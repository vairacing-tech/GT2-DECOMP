# GT2-DECOMP

Faithful decompilation work for **Gran Turismo 2 – Simulation Mode (NTSC-U 1.2)**, with a later path toward native Windows and Android execution.

## Project lineage and attribution

GT2-DECOMP is maintained as an independent project, based on the public decompilation work from [`ginryuoku/gt2-reversing`](https://github.com/ginryuoku/gt2-reversing).

That upstream project provided the initial Simulation Mode decompilation foundation. This repository builds on that base with project-specific goals, tooling, documentation, runtime planning, and compatibility policy for a future native Windows/Android runtime.

Current project-specific layers include:

- reproducible ingestion of user-provided disc images;
- version manifests for vanilla and content-modified compatible discs;
- explicit separation between extracted game data and source code;
- future-facing contracts for runtime profiles and resource packs.

## Current status

- Base disc target: `SCUS_944.88` from **Simulation Mode NTSC-U 1.2**.
- Upstream decomp coverage: main executable plus separated overlays, with the broader GT Mode reconstruction still in progress.
- Native runtime: architecture only; not implemented yet.
- Supported inputs today:
  - vanilla `.bin/.cue` Simulation Mode NTSC-U 1.2;
  - structurally compatible modified images, such as user-patched Project A-Spec discs.

## Repository layout

- `src/`, `include/`, `config/`: upstream decompilation source and configuration.
- `tools/ingest_disc.py`: validates and extracts supported user-provided disc images.
- `runtime/config/profiles.json`: public runtime profile contract (`enhanced` / `original`).
- `resource_packs/schema.json`: initial manifest contract for future PAL-resource import packs.
- `docs/`: project decisions, architecture, roadmap, and the current Simulation Mode blocker order.
- `workspace/`: generated disc manifests and extracted files; ignored by Git.

## Quick start

### 1. Ingest the game disc

From the repository root:

```powershell
python .\tools\ingest_disc.py `
  ".\Game Files\Gran Turismo 2 (Simulation Mode) (v1.2).bin" `
  --prepare-decomp
```

This will:

1. validate the disc layout and identify the build;
2. extract the required top-level files into `workspace/discs/<disc-id>/files/`;
3. write a manifest to `workspace/discs/<disc-id>/manifest.json`;
4. copy `SCUS_944.88` and `GT2.OVL` into the upstream-compatible `config/gt2_us12_simdisk/orig_bin/` folder.

If the overall disc hash is not the known vanilla image but the disc still matches the expected US 1.2 structure, the tool classifies it as `compatible_modified` rather than rejecting it. That is the intended path for Project A-Spec-style patched images.

For the current single-track Simulation Mode image, the `.bin` file is sufficient for decompilation work. The ingester also accepts `.cue`, but it is optional for this disc rather than a project requirement.

### 2. Build the matching decompilation target

The matching build flow still follows the upstream Linux/WSL2 workflow because it relies on historical MIPS toolchains. See `docs/DECOMP_BUILD.md` for the practical setup notes.

```bash
git submodule update --init --recursive
python3 -m pip install -r requirements-decomp.txt
python3 build_gen.py > build.ninja
ninja
```

The native Windows/Android runtime is a later workstream; the immediate priority remains faithful reconstruction of the original game logic.

## Design rules

- **Fidelity first** for the reconstructed game logic.
- **Enhanced by default** for the eventual native runtime, with an `original` profile preserved for regression testing and comparison.
- **No copyrighted game data** is committed to the repository.
- **DuckStation feature parity, not `.cht` file compatibility**: improvements such as metric units, higher draw distance, higher LOD, and expanded buffers should become native options.
- **Project A-Spec compatibility through user-supplied patched discs**, not through bundled patch data.
- **Future PAL translation import through resource packs**, without requiring full PAL executable support in the first milestone.

## Verification

Run the Python tests with:

```powershell
python -m unittest discover -s tests -v
```

Then validate your own disc image with:

```powershell
python .\tools\ingest_disc.py ".\Game Files\Gran Turismo 2 (Simulation Mode) (v1.2).bin"
```

## Upstream credit

The decompilation core, original build system, and a substantial amount of reverse-engineering work come from the public [`gt2-reversing`](https://github.com/ginryuoku/gt2-reversing) project. Project-specific additions in this repository are intended to build on that work, not replace or obscure it.
