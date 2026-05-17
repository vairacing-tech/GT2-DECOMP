from __future__ import annotations

import argparse
import shutil
from pathlib import Path

from gt2_disc import DiscValidationError, extract_entries, inspect_disc, write_manifest


EXTRACTED_FILES = (
    "SCUS_944.88",
    "GT2.OVL",
    "GT2.VOL",
    "MUSIC.DAT",
    "SYSTEM.CNF",
)
DECOMP_INPUT_FILES = (
    "SCUS_944.88",
    "GT2.OVL",
)


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Validate and ingest a Gran Turismo 2 Simulation Mode NTSC-U 1.2 disc image."
    )
    parser.add_argument("image", type=Path, help="Path to a raw MODE2/2352 .bin image or companion .cue file.")
    parser.add_argument(
        "--workspace-root",
        type=Path,
        default=Path("workspace/discs"),
        help="Directory where extracted disc workspaces are created.",
    )
    parser.add_argument(
        "--prepare-decomp",
        action="store_true",
        help="Copy SCUS_944.88 and GT2.OVL into config/gt2_us12_simdisk/orig_bin/.",
    )
    return parser


def main() -> int:
    args = build_parser().parse_args()

    try:
        inspection = inspect_disc(args.image)
    except DiscValidationError as exc:
        raise SystemExit(f"error: {exc}") from exc

    disc_root = args.workspace_root / inspection.disc_id
    files_dir = disc_root / "files"
    manifest_path = disc_root / "manifest.json"

    extract_entries(inspection, EXTRACTED_FILES, files_dir)
    write_manifest(inspection, manifest_path)

    if args.prepare_decomp:
        decomp_dir = Path("config/gt2_us12_simdisk/orig_bin")
        decomp_dir.mkdir(parents=True, exist_ok=True)
        for name in DECOMP_INPUT_FILES:
            shutil.copy2(files_dir / name, decomp_dir / name)

    print(f"disc_id: {inspection.disc_id}")
    print(f"profile: {inspection.profile}")
    print(f"variant: {inspection.variant}")
    print(f"manifest: {manifest_path}")
    print(f"files: {files_dir}")
    if args.prepare_decomp:
        print("prepared decomp inputs: config/gt2_us12_simdisk/orig_bin")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
