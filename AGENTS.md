# AGENTS.md

## Project mission

Build a faithful decompilation of **Gran Turismo 2 – Simulation Mode (NTSC-U 1.2)**, then use that recovered game core as the basis for future native execution on **Windows** and **Android**.

The first major gameplay milestone is not a tech demo. It is a complete Simulation Mode experience:

1. boot;
2. create or load a save;
3. navigate GT Mode menus;
4. buy a car;
5. manage the garage;
6. obtain a license;
7. enter and complete a race;
8. save, restart, reload, and continue progression successfully.

## Core priorities

1. **Fidelity first for game logic**
   - Prefer understanding and matching original behavior before replacing systems with approximations.
   - Treat the PS1 release as the reference implementation.

2. **Native runtime later, but architected deliberately**
   - The eventual runtime should expose:
     - `enhanced` as the default profile;
     - `original` as the preservation/regression profile.
   - Enhanced features should be native equivalents of known community patches, not a dependency on loading `.cht` cheat files directly.

3. **No copyrighted assets in Git**
   - User-provided discs and extracted files belong in ignored paths such as `Game Files/` and `workspace/`.
   - Source, tooling, manifests, and schemas belong in the repository.

## Current technical baseline

- Upstream decompilation base: `ginryuoku/gt2-reversing`.
- Primary target disc: `SCUS_944.88` from **Simulation Mode NTSC-U 1.2**.
- Existing upstream strengths:
  - correct disc family;
  - split executable/overlay model;
  - recovered source, symbols, headers, and build configuration.
- Existing upstream limitations:
  - build flow is still Linux/WSL-oriented;
  - `GT2.OVL` is not yet rebuilt as a fully matching archive container;
  - Simulation Mode is still far from fully recovered.

## Repository conventions

### Source of truth

- Matching decompilation source lives under:
  - `src/`
  - `include/`
  - `config/`
- Project-specific support layers live under:
  - `tools/`
  - `docs/`
  - `runtime/`
  - `resource_packs/`

### Disc ingestion

Use the ingestion pipeline instead of manually copying files:

```powershell
python .\tools\ingest_disc.py ".\Game Files\Gran Turismo 2 (Simulation Mode) (v1.2).cue" --prepare-decomp
```

Expected behavior:

- exact known US 1.2 image -> `vanilla`;
- structurally valid modified US 1.2 image -> `compatible_modified`;
- incompatible disc -> reject with a clear diagnostic.

### Build workflow

- Keep the matching decomp build on Linux/WSL while that remains the working path for the historical MIPS toolchain.
- Prefer **WSL2** over WSL1 on Windows; the current historical compiler bundle does not run correctly under the audited WSL1 setup.
- Do not spend project energy porting the whole decomp toolchain to Windows unless that becomes an explicit priority later.
- The final user-facing runtime should still target native Windows and Android.

Known audited state as of **2026-05-16**:

- overlays `gt2_01.exe` through `gt2_06.exe` rebuild and match;
- `SCUS_944.88` also rebuilds and matches exactly;
- `PDENT2_OBJ_B8` and `PDENT2_OBJ_BC` must remain internal to `PadGetState` in the main executable split, or the build grows by one extra `nop`.

## Compatibility policy

### Community patch-style improvements

Support the **capabilities**, not the original cheat-file format:

- metric units;
- increased draw distance;
- higher LOD;
- expanded polygon buffers;
- similar future quality-of-life improvements where behavior is understood.

These belong in the eventual native runtime profile system:

- `enhanced`: enabled by default;
- `original`: disabled for preservation and regression checks.

### Project A-Spec

- Support A-Spec through **user-supplied already-patched disc images**.
- Do not bundle patch data.
- Do not build a bespoke mod platform before Simulation Mode is stable.

### PAL translation

- Near-term goal: import PAL-derived text/resources over the NTSC-U 1.2 base.
- Non-goal for the first milestone: full PAL executable support.
- Future localization work should use resource packs compatible with `resource_packs/schema.json`.

## Milestone roadmap

### Milestone 0 — Foundation

- Preserve and adopt the upstream decomp base.
- Keep disc ingestion reproducible.
- Keep user content out of Git.
- Maintain public contracts for runtime profiles and resource packs.

### Milestone 1 — Faithful Simulation Mode core

- Recover the systems required for the complete GT Mode flow:
  - boot;
  - loaders;
  - menus;
  - dealerships;
  - garage;
  - licenses;
  - races;
  - saves and progression.
- Compare behavior against the original release before modernizing or abstracting.

### Milestone 2 — Native host prototype

- Introduce platform boundaries for:
  - input;
  - rendering;
  - audio;
  - storage;
  - host services.
- Target Windows first.
- Target Android later with **gamepad-first** support.

### Milestone 3 — Content compatibility

- Keep patched compatible discs working.
- Add resource-pack loading for localization experiments.
- Defer Arcade Disc, full PAL parity, and a broad mod ecosystem until the Simulation Mode core is stable.

## Testing expectations

### Ingestion

- Accept vanilla US 1.2 `.bin/.cue`.
- Accept structurally compatible modified discs.
- Reject incompatible discs clearly.

### Decompilation

- Preserve reproducible builds where matching is already achieved.
- Validate reconstructed behavior against the original game wherever practical.

### Gameplay acceptance

The milestone is not complete until the full Simulation Mode progression loop works end to end.

### Runtime acceptance

- `original` profile should be suitable for comparisons against the original release.
- `enhanced` profile should provide coherent modern defaults without mutating the faithful core.

## Working principles for agents

- Prefer extending existing project structure over creating parallel systems.
- Keep the boundary between **faithful core** and **future host/runtime** explicit.
- When uncertain, choose the path that preserves correctness and reversibility.
- Document decisions that affect compatibility, versioning, or future porting.
- Do not silently broaden scope to Arcade Disc, full PAL support, or a generalized mod platform.
- When adding new tooling, keep it reproducible, inspectable, and safe for user-provided copyrighted data.
