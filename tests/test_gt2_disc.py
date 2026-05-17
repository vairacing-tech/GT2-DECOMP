from __future__ import annotations

import tempfile
import unittest
from pathlib import Path

import sys

TOOLS_DIR = Path(__file__).resolve().parents[1] / "tools"
sys.path.insert(0, str(TOOLS_DIR))

from gt2_disc import (
    DiscValidationError,
    PRIMARY_VOLUME_DESCRIPTOR_LBA,
    RAW_SECTOR_SIZE,
    USER_DATA_OFFSET,
    USER_DATA_SIZE,
    inspect_disc,
    parse_boot_executable,
    resolve_image_path,
)


class ParseBootExecutableTests(unittest.TestCase):
    def test_parses_expected_boot_path(self) -> None:
        system_cnf = "BOOT = cdrom:\\SCUS_944.88;1\r\nTCB = 4\r\n"
        self.assertEqual(parse_boot_executable(system_cnf), "SCUS_944.88")

    def test_rejects_missing_boot_line(self) -> None:
        with self.assertRaises(DiscValidationError):
            parse_boot_executable("TCB = 4\r\n")


class InspectDiscTests(unittest.TestCase):
    def test_accepts_structurally_compatible_modified_disc(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            image = Path(tmp) / "compatible.bin"
            build_test_disc(image)

            inspection = inspect_disc(image)

            self.assertEqual(inspection.profile, "gt2_us12_simdisk")
            self.assertEqual(inspection.variant, "compatible_modified")
            self.assertEqual(inspection.boot_executable, "SCUS_944.88")

    def test_rejects_disc_with_unexpected_boot_executable(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            image = Path(tmp) / "wrong-boot.bin"
            build_test_disc(image, boot_executable="SLUS_000.00")

            with self.assertRaises(DiscValidationError):
                inspect_disc(image)

    def test_accepts_cue_file_entrypoint(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            image = Path(tmp) / "compatible.bin"
            cue = Path(tmp) / "compatible.cue"
            build_test_disc(image)
            cue.write_text('FILE "compatible.bin" BINARY\r\n  TRACK 01 MODE2/2352\r\n', encoding="utf-8")

            inspection = inspect_disc(cue)

            self.assertEqual(inspection.image_path, image.resolve())


class ResolveImagePathTests(unittest.TestCase):
    def test_rejects_cue_without_file_entry(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            cue = Path(tmp) / "broken.cue"
            cue.write_text("TRACK 01 MODE2/2352\r\n", encoding="utf-8")

            with self.assertRaises(DiscValidationError):
                resolve_image_path(cue)


def build_test_disc(path: Path, boot_executable: str = "SCUS_944.88") -> None:
    entries = {
        "SYSTEM.CNF;1": (23, f"BOOT = cdrom:\\{boot_executable};1\r\n".encode("ascii")),
        "SCUS_944.88;1": (24, b"PS-X EXE"),
        "GT2.OVL;1": (25, b"OVL"),
        "GT2.VOL;1": (26, b"GTFS"),
        "MUSIC.DAT;1": (27, b"MUSIC"),
    }

    sector_count = 32
    image = bytearray(sector_count * RAW_SECTOR_SIZE)

    def write_user_sector(lba: int, data: bytes) -> None:
        start = lba * RAW_SECTOR_SIZE + USER_DATA_OFFSET
        image[start : start + len(data)] = data

    pvd = bytearray(USER_DATA_SIZE)
    pvd[:7] = b"\x01CD001\x01"
    pvd[40:72] = b"GRANTURISMO2".ljust(32, b" ")
    root_record = build_dir_record(b"\x00", 22, USER_DATA_SIZE, is_dir=True)
    pvd[156 : 156 + len(root_record)] = root_record
    write_user_sector(PRIMARY_VOLUME_DESCRIPTOR_LBA, pvd)

    root_dir = bytearray(USER_DATA_SIZE)
    cursor = 0
    for record in (
        build_dir_record(b"\x00", 22, USER_DATA_SIZE, is_dir=True),
        build_dir_record(b"\x01", 22, USER_DATA_SIZE, is_dir=True),
        *(
            build_dir_record(name.encode("ascii"), lba, len(data), is_dir=False)
            for name, (lba, data) in entries.items()
        ),
    ):
        root_dir[cursor : cursor + len(record)] = record
        cursor += len(record)
    write_user_sector(22, root_dir)

    for _, (lba, data) in entries.items():
        write_user_sector(lba, data)

    path.write_bytes(image)


def build_dir_record(name: bytes, extent_lba: int, size: int, *, is_dir: bool) -> bytes:
    record_length = 33 + len(name)
    if record_length % 2 == 1:
        record_length += 1

    record = bytearray(record_length)
    record[0] = record_length
    record[2:6] = extent_lba.to_bytes(4, "little")
    record[6:10] = extent_lba.to_bytes(4, "big")
    record[10:14] = size.to_bytes(4, "little")
    record[14:18] = size.to_bytes(4, "big")
    record[25] = 0x02 if is_dir else 0x00
    record[28:30] = (1).to_bytes(2, "little")
    record[30:32] = (1).to_bytes(2, "big")
    record[32] = len(name)
    record[33 : 33 + len(name)] = name
    return bytes(record)


if __name__ == "__main__":
    unittest.main()
