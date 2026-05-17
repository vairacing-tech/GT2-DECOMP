# Matching decomp build workflow

The decompilation build remains Linux/WSL-oriented for now. That is intentional: the current matching toolchain uses historical MIPS compilers and Linux-side binutils, and preserving a working fidelity-first pipeline matters more than prematurely porting every build step.

## Recommended environment

- Ubuntu or another Linux distribution;
- **WSL2**, not WSL1, when working from Windows;
- keep the build checkout inside the Linux filesystem rather than an NTFS mountpoint;
- install Python 3, Ninja, MIPS binutils, and the 32-bit runtime libraries needed by the bundled historical compilers.

The audited working environment on **2026-05-16** was Ubuntu 22.04 under WSL2 with the Python package versions pinned in `requirements-decomp.txt`.

WSL1 was tested and rejected for this workflow: the bundled historical 32-bit compilers fail there with `Exec format error`.

## Minimal command flow

```bash
git submodule update --init --recursive
python3 -m pip install -r requirements-decomp.txt
python3 build_gen.py > build.ninja
ninja
```

## Current audited result

The matching build currently succeeds for the separated overlay executables:

- `build/gt2_01.exe.ok`
- `build/gt2_02.exe.ok`
- `build/gt2_03.exe.ok`
- `build/gt2_04.exe.ok`
- `build/gt2_05.exe.ok`
- `build/gt2_06.exe.ok`

The main executable also matches exactly:

- original SHA1: `3030aa271c0a4022fc69ce09d76a6bc75e69a32a`
- rebuilt SHA1: `3030aa271c0a4022fc69ce09d76a6bc75e69a32a`

The key fix was to stop splitting `PDENT2_OBJ_B8` and `PDENT2_OBJ_BC` out of `PadGetState` in `mainexe_symbol_addrs.txt`. They are internal labels in the original layout, not standalone functions.

## Why not Windows-native yet?

The future game runtime is expected to run natively on Windows. The matching decompilation pipeline is a separate concern, and forcing it onto Windows before the game core is understood would spend effort on infrastructure rather than on recovering GT2 itself.
