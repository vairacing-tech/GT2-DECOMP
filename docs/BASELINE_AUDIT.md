# Baseline audit: `gt2-reversing`

## Decision

Adopt `gt2-reversing` as the initial technical foundation for GT2-DECOMP.

## Why it passes

- It targets the exact disc family this project needs first: `SCUS_944.88` from US 1.2 Simulation Mode.
- It already models the executable plus overlay structure rather than treating the game as a monolithic blob.
- It contains meaningful recovered source, symbols, headers, and build configuration that would be costly to rediscover.
- Its matching-first workflow aligns with the project's fidelity-first direction.

## Known limitations accepted at adoption time

- The matching build flow is Linux/WSL-oriented because it depends on historical MIPS toolchains.
- Overlay rebuilding is still incomplete at archive level: separated overlay executables are produced, but `GT2.OVL` is not yet reconstructed as a fully matching container.
- Coverage is strongest in the main executable and early overlays; completing Simulation Mode still requires substantial reverse-engineering work.

## Phase 0 verification — 2026-05-16

The upstream base was validated against the user-provided **Simulation Mode NTSC-U 1.2** disc using a Linux checkout inside WSL2.

### Environment findings

- `Ubuntu-20.04` under **WSL1** is not suitable for the current matching toolchain: the bundled historical 32-bit MIPS compilers fail with `Exec format error` even after installing i386 runtime libraries.
- `Ubuntu` under **WSL2** works for the same toolchain.
- The working audit setup used:
  - Ubuntu 22.04;
  - `splat64==0.29.0`;
  - `spimdisasm==1.40.3`;
  - `rabbitizer==1.16.0`;
  - Ninja, `binutils-mips-linux-gnu`, and the required 32-bit compatibility libraries.

### Build result

- Matching overlay executables currently rebuild successfully:
  - `gt2_01.exe`
  - `gt2_02.exe`
  - `gt2_03.exe`
  - `gt2_04.exe`
  - `gt2_05.exe`
  - `gt2_06.exe`
- The main executable now also rebuilds exactly:
  - original `SCUS_944.88`: `3030aa271c0a4022fc69ce09d76a6bc75e69a32a`
  - rebuilt `scus_944.88`: `3030aa271c0a4022fc69ce09d76a6bc75e69a32a`

The last mismatch was caused by over-splitting two internal labels inside `PadGetState`:

- `PDENT2_OBJ_B8`
- `PDENT2_OBJ_BC`

When those labels were treated as separate functions, the generated `INCLUDE_ASM` boundary inserted one extra `nop`, making the rebuilt main executable 4 bytes larger than the original. Removing those two entries from `mainexe_symbol_addrs.txt` keeps them inside the containing assembly block and restores exact matching.

### Compatibility adjustments required on a modern setup

Two small source-level fixes were needed before the current tree would build with the audited toolchain:

- `include/macro.inc`
  - add no-op support for newer `nonmatching` / `enddlabel` markers emitted by generated assembly;
- `src/ovr0/gt2_main_task0a_ovr_func1.c`
  - remove a duplicate local `s32` typedef that conflicts with `common.h`.

These are build-compatibility fixes, not gameplay changes.

## Consequence for this repository

- Upstream decompilation code remains the canonical source base.
- New project work should avoid entangling user-owned disc data with tracked source files.
- Native runtime work must be layered around the faithful core, not replace it prematurely.
- The decompilation baseline is now strong enough to move from setup work into the first gameplay-critical analysis pass: boot, overlay handoff, and the loader chain.
