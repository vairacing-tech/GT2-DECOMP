from __future__ import annotations

import hashlib
import json
import math
from dataclasses import dataclass
from pathlib import Path
from typing import BinaryIO, Iterable


RAW_SECTOR_SIZE = 2352
USER_DATA_OFFSET = 24
USER_DATA_SIZE = 2048
PRIMARY_VOLUME_DESCRIPTOR_LBA = 16
KNOWN_VANILLA_SHA1 = "c4813703d2ad440ed36670c1ac2c1a66c9dc673d"
EXPECTED_BOOT = "SCUS_944.88"
EXPECTED_VOLUME_ID = "GRANTURISMO2"
REQUIRED_TOP_LEVEL_FILES = {
    "SCUS_944.88",
    "GT2.OVL",
    "GT2.VOL",
    "MUSIC.DAT",
    "SYSTEM.CNF",
}


class DiscValidationError(RuntimeError):
    """Raised when a disc image is not a supported GT2 target."""


@dataclass(frozen=True)
class IsoEntry:
    name: str
    extent_lba: int
    size: int
    is_dir: bool


@dataclass(frozen=True)
class DiscInspection:
    image_path: Path
    sha1: str
    volume_id: str
    system_cnf: str
    boot_executable: str
    entries: dict[str, IsoEntry]
    variant: str

    @property
    def disc_id(self) -> str:
        return self.sha1[:12]

    @property
    def profile(self) -> str:
        return "gt2_us12_simdisk"

    def to_manifest(self) -> dict[str, object]:
        return {
            "schema_version": 1,
            "disc_id": self.disc_id,
            "profile": self.profile,
            "variant": self.variant,
            "image": {
                "filename": self.image_path.name,
                "sha1": self.sha1,
            },
            "iso9660": {
                "volume_id": self.volume_id,
                "boot_executable": self.boot_executable,
                "system_cnf": self.system_cnf,
            },
            "files": {
                name: {
                    "extent_lba": entry.extent_lba,
                    "size": entry.size,
                }
                for name, entry in sorted(self.entries.items())
                if not entry.is_dir and name not in {"\x00", "\x01"}
            },
        }


def sha1_file(path: Path) -> str:
    digest = hashlib.sha1()
    with path.open("rb") as handle:
        while chunk := handle.read(1024 * 1024):
            digest.update(chunk)
    return digest.hexdigest()


def _read_user_sector(handle: BinaryIO, lba: int) -> bytes:
    handle.seek(lba * RAW_SECTOR_SIZE + USER_DATA_OFFSET)
    data = handle.read(USER_DATA_SIZE)
    if len(data) != USER_DATA_SIZE:
        raise DiscValidationError(f"Sector {lba} is truncated.")
    return data


def _decode_iso_name(raw: bytes) -> str:
    if raw in {b"\x00", b"\x01"}:
        return raw.decode("latin-1")
    name = raw.decode("ascii")
    return name.split(";")[0]


def _read_directory(handle: BinaryIO, extent_lba: int, size: int) -> dict[str, IsoEntry]:
    sector_count = math.ceil(size / USER_DATA_SIZE)
    data = b"".join(_read_user_sector(handle, extent_lba + offset) for offset in range(sector_count))
    entries: dict[str, IsoEntry] = {}
    cursor = 0

    while cursor < size:
        record_length = data[cursor]
        if record_length == 0:
            cursor = ((cursor // USER_DATA_SIZE) + 1) * USER_DATA_SIZE
            continue

        record = data[cursor : cursor + record_length]
        name_length = record[32]
        name = _decode_iso_name(record[33 : 33 + name_length])
        entry = IsoEntry(
            name=name,
            extent_lba=int.from_bytes(record[2:6], "little"),
            size=int.from_bytes(record[10:14], "little"),
            is_dir=bool(record[25] & 0x02),
        )
        entries[name] = entry
        cursor += record_length

    return entries


def _read_entry_bytes(handle: BinaryIO, entry: IsoEntry) -> bytes:
    sector_count = math.ceil(entry.size / USER_DATA_SIZE)
    data = b"".join(_read_user_sector(handle, entry.extent_lba + offset) for offset in range(sector_count))
    return data[: entry.size]


def inspect_disc(image_path: Path) -> DiscInspection:
    image_path = resolve_image_path(image_path).resolve()
    if not image_path.is_file():
        raise DiscValidationError(f"Disc image not found: {image_path}")

    with image_path.open("rb") as handle:
        pvd = _read_user_sector(handle, PRIMARY_VOLUME_DESCRIPTOR_LBA)
        if pvd[:7] != b"\x01CD001\x01":
            raise DiscValidationError("Image is not a supported raw MODE2/2352 ISO9660 PlayStation disc.")

        volume_id = pvd[40:72].decode("ascii", errors="ignore").rstrip(" ")
        if volume_id != EXPECTED_VOLUME_ID:
            raise DiscValidationError(
                f"Unexpected ISO volume id '{volume_id}'. Expected '{EXPECTED_VOLUME_ID}'."
            )

        root_record = pvd[156:190]
        root_extent = int.from_bytes(root_record[2:6], "little")
        root_size = int.from_bytes(root_record[10:14], "little")
        entries = _read_directory(handle, root_extent, root_size)

        missing = sorted(REQUIRED_TOP_LEVEL_FILES - entries.keys())
        if missing:
            raise DiscValidationError(f"Missing required top-level file(s): {', '.join(missing)}")

        system_cnf = _read_entry_bytes(handle, entries["SYSTEM.CNF"]).decode(
            "ascii", errors="replace"
        )
        boot_executable = parse_boot_executable(system_cnf)
        if boot_executable != EXPECTED_BOOT:
            raise DiscValidationError(
                f"Unexpected boot executable '{boot_executable}'. Expected '{EXPECTED_BOOT}'."
            )

    image_sha1 = sha1_file(image_path)
    variant = "vanilla" if image_sha1 == KNOWN_VANILLA_SHA1 else "compatible_modified"

    return DiscInspection(
        image_path=image_path,
        sha1=image_sha1,
        volume_id=volume_id,
        system_cnf=system_cnf,
        boot_executable=boot_executable,
        entries=entries,
        variant=variant,
    )


def resolve_image_path(path: Path) -> Path:
    path = path.resolve()
    if path.suffix.lower() != ".cue":
        return path

    if not path.is_file():
        raise DiscValidationError(f"CUE file not found: {path}")

    for line in path.read_text(encoding="utf-8").splitlines():
        stripped = line.strip()
        if not stripped.upper().startswith("FILE "):
            continue

        parts = stripped.split('"')
        if len(parts) < 3:
            raise DiscValidationError("CUE FILE entry must quote the referenced image filename.")
        referenced = path.parent / parts[1]
        if not referenced.is_file():
            raise DiscValidationError(f"CUE references missing image file: {referenced}")
        return referenced

    raise DiscValidationError("CUE file does not contain a FILE entry.")


def parse_boot_executable(system_cnf: str) -> str:
    for line in system_cnf.splitlines():
        key, _, value = line.partition("=")
        if key.strip().upper() == "BOOT":
            normalized = value.strip().replace("\\", "/")
            filename = normalized.rsplit("/", 1)[-1]
            return filename.split(";")[0]
    raise DiscValidationError("SYSTEM.CNF does not define a BOOT entry.")


def extract_entries(
    inspection: DiscInspection,
    names: Iterable[str],
    destination_dir: Path,
) -> list[Path]:
    destination_dir.mkdir(parents=True, exist_ok=True)
    written: list[Path] = []

    with inspection.image_path.open("rb") as handle:
        for name in names:
            entry = inspection.entries[name]
            if entry.is_dir:
                continue
            target = destination_dir / name
            target.write_bytes(_read_entry_bytes(handle, entry))
            written.append(target)

    return written


def write_manifest(inspection: DiscInspection, path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(inspection.to_manifest(), indent=2) + "\n", encoding="utf-8")
