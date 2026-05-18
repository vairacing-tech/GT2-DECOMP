# GT2.VOL cached path map

`gt2_ovr0_vol_build_file_indices_cache()` walks the 248-entry `gt2_vol_cached_paths` table at boot and resolves each path to a packed GTFS file-entry index in `gt2_vol_cached_dir_indices`.

That makes the slot number a compact symbolic asset ID used throughout the executable. The table is broader than its old "directory index" nickname suggested: it contains files as well as directories, and it spans data needed by boot, menus, races, replay handling, and sound.

## Slot families

| Slot range | Contents |
| --- | --- |
| `0x00`–`0x0B` | root metadata and car/course databases |
| `0x0C`–`0x45` | arcade UI assets and locale variants |
| `0x46`–`0x6D` | shared world/car assets, carparam packs, and course object roots |
| `0x6E`–`0xBE` | dirt-course object banks |
| `0xBF`–`0xC1` | engine resources |
| `0xC2`–`0xE0` | race font plus GT Mode menu/resource packs |
| `0xE1`–`0xE3` | license data |
| `0xE4`–`0xE9` | replay ranges |
| `0xEA`–`0xF7` | sound sequences and instrument banks |

Representative slots already visible in recovered or inspected callers:

| Slot | Path | Current evidence |
| --- | --- | --- |
| `0x01` | `/.carinfoa` | loaded by `gt2_main_arcade_func4` through `gt2_main_task0b11` |
| `0x04` | `/.ccjapanese` | loaded by an OVR5 menu path through `gt2_main_task0b11` |
| `0x06` | `/.crsinfo` | loaded during bootstrap by `gt2_main_task0b1` |
| `0xC2` | `/font/racefont.dat` | queried by `gt2_main_shared_arcaderace_func3` |
| `0xC4` | `/gtmenu/commonpic.idx` | loaded by an OVR5 GT-menu path |
| `0xE4` | `/replay/scea.000` | lower bound used by `gt2_main_task0b7` |
| `0xE5` | `/replay/scea.999` | upper bound used by `gt2_main_task0b7` |
| `0xF7` | `/sound/sys.ins` | loaded directly by `gt2_main_task0b2` |

## Current consumer vocabulary

The recovered code exposes four small wrappers around the cache:

| Function | Behavior |
| --- | --- |
| `gt2_main_task0b11(slot, dst)` | resolves `slot` through `gt2_vol_cached_dir_indices` and loads the file through the normal CD-read path |
| `gt2_main_shared_arcaderace_func32(slot)` | resolves `slot` and returns the file-data sector offset |
| `gt2_main_shared_arcaderace_func33(slot)` | resolves `slot` and returns the file span encoded by adjacent GTFS header entries through recovered helper `gt2_main_task0b2101()` |
| `gt2_main_shared_gtracemenu_func0(slot, dst)` | resolves `slot` and loads through the alternate race/GT/arcade read path |

Two more patterns matter:

- `gt2_main_task0b7()` subtracts cached replay endpoints `0xE4` and `0xE5` to derive the SCEA replay-count span.
- `gt2_main_task0b210()` and several OVR5 helpers index the same cache directly through `D_801E2EF0`; those sites should eventually use the public `gt2_vol_cached_dir_indices` name once they are recovered.

## Why this matters

For later GT Mode recovery, many apparently opaque loader arguments are already symbolic. A call such as `gt2_main_task0b11(0xC4, ...)` is not just "load file 196"; it is specifically "load `/gtmenu/commonpic.idx`". Converting those raw slots into named constants or enums will make menu, garage, license, and race setup paths much easier to read without changing faithful behavior.
