# Simulation Mode blocker order

This is the recommended decompilation order after the Phase 0 audit. It is intentionally dependency-driven: each item should make the next one easier to validate.

## 0. Baseline status

The Phase 0 baseline is now clean:

- `SCUS_944.88` matches exactly;
- overlays `gt2_01.exe` through `gt2_06.exe` match exactly;
- the `PadGetState` split issue has been resolved by keeping `PDENT2_OBJ_B8` and `PDENT2_OBJ_BC` inside the containing assembly block.

That means the next work should now move into gameplay-critical understanding rather than more setup.

## 1. Boot and executable handoff

Current footholds already visible in the tree include:

- `src/start/gt2_init.c`
- `src/start/gt2_main.c`
- `src/start/gt2_load_overlay_default.c`
- `src/ovr0/gt2_sysinit.c`
- `src/ovr0/gt2_show_vendor_bootlogo_task0.c`

Goal:

- understand the full route from process start to the first playable GT Mode state;
- document overlay transitions and the ownership boundary between the main executable and overlay 0.

Why next:

- every later gameplay test depends on deterministic startup;
- boot work also reveals the loader and task model used by the rest of the game.

## 2. Disc / volume loading

Existing recovered pieces:

- `src/start/gt2_main_task_083_file_loader0.c`
- `src/start/gt2_main_vol_get_file_data_sector_offset.c`
- `src/ovr0/gt2_ovr0_vol_gtfs_init.c`
- `src/ovr0/gt2_ovr0_vol_build_file_indices_cache.c`
- `src/ovr0/gt2_ovr0_vol_search_vol_dir.c`

Goal:

- recover enough of the `GT2.VOL` access path to trace assets and game data deterministically;
- make future Project A-Spec and PAL-resource investigations cheaper by understanding the content-loading contract early.

Why before menus:

- GT Mode is asset-heavy;
- unknown loader behavior obscures failures in almost every later subsystem.

## 3. Save / load and card-state flow

Known footholds:

- `src/start/gt2_save_crc32.c`
- the unrecovered PlayStation card / pad support area in the `lib` segment around `InitCARD`, `_card_*`, and related SDK helpers.

Goal:

- trace create-save, load-save, CRC validation, and persistence boundaries end to end;
- establish a reproducible “new game -> save -> restart -> load” validation loop.

Why before broad GT Mode decomp:

- progression cannot be validated without persistence;
- save data often exposes compact models for garage, money, licenses, and championship state.

## 4. GT Mode menus and progression graph

Current signal:

- there are a few named menu helpers in `src/start/`;
- overlays `2` through `5` still have very sparse recovered source in the current tree, which strongly suggests a large remaining surface here.

Goal:

- map the menu state machine required for:
  - home / world map;
  - dealerships;
  - garage;
  - licenses;
  - event entry;
  - post-race return.

Why after loaders and saves:

- menu behavior depends on loaded resources and persistent player state;
- once save/load is understood, menu-side state changes become much easier to verify.

## 5. Race entry, result application, and return to GT Mode

Current footholds:

- several `gt2_main_race_*` and shared race helpers already exist under `src/start/`.

Goal:

- make one complete gameplay loop auditable:
  - enter race;
  - run session;
  - finish;
  - apply rewards / progression;
  - return to GT Mode;
  - save and reload successfully afterward.

Why this closes the first milestone:

- it converts isolated subsystem understanding into the exact end-to-end acceptance path defined for Simulation Mode.

## Immediate next action

The best next technical move is now:

1. begin a callgraph-and-state pass over the boot / loader chain listed above;
2. document overlay transitions and task ownership during startup;
3. then continue into the `GT2.VOL` loader path before touching broader save or menu work.
