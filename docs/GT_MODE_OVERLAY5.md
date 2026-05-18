# GT Mode overlay 5 notes

The recent `ovr5_17` recovery work has exposed three useful local families inside the GT Mode overlay without changing behavior:

## 1. Compact active-entry accessors

These functions all read the current 8-byte record selected by `D_800529A2` from the table rooted at `D_800B9510`:

| Function | Field |
| --- | --- |
| `func_80020BDC()` | word at `+0x0` |
| `func_80020C00()` | signed byte at `+0x7` |
| `func_80020C24()` | low 24 bits of word at `+0x4` |

That is enough evidence to treat the table as a compact record array rather than as unrelated globals.

## 2. Relative-offset blob helpers

Several small helpers operate on packed blobs that store offsets relative to their own base address:

| Function | Behavior |
| --- | --- |
| `func_80022368(base, index)` | resolves `base + *(u16*)(base + index * 2 + 8)` |
| `func_8002237C(base, index)` | resolves a secondary table through `D_800A8D80` |
| `func_800223B0(base, index)` | resolves `base + *(u16*)(base + index * 2)` |
| `func_800224B0(base, index)` | resolves `base + *(u16*)(base + index * 4)` |
| `func_800224C4(base, index)` | returns `base + index * 4 + 2` |
| `func_800224D4()` | returns the shared blob rooted at `D_800B9544` |

The callers above them are still partly unrecovered, but this already makes the data format visible: the overlay is walking compact offset tables, not arbitrary pointer graphs.

## 3. Small loader-state wrappers

The next layer up is now partly in C as well:

| Function | Behavior |
| --- | --- |
| `func_80022634(index, out_count, out_items)` | resolves a packed bucket and returns its element count plus item pointer |
| `func_800226A0(state, arg1, arg2)` | clears a `0x2BC`-byte state block, then initializes it |
| `func_800226F4(state)` | forwards to the state cleanup routine |
| `func_80022714(state, arg1)` | computes a 4-byte-aligned read destination inside the state |
| `func_80022758(state, slot)` | loads a cached asset into that destination and finalizes it |
| `func_80022838(state)` | conditionally releases active payload state, then clears the active flag |
| `func_80022874()` | initializes the shared loader state used by the overlay |
| `func_800228D4(index)` | switches the shared loader to a new cached slot on demand |
| `func_80022934()` | resets the active cached-slot marker and tears the loader down |

Those helpers now share the recovered `gt2_ovr5_loader_state` shape from
`include/gt2_ovr5_loader.h`; the currently visible fields are:

| Offset | Field |
| --- | --- |
| `0x000` | `base` |
| `0x00C` | `payload` start |
| `0x2B4` | `read_dst` |
| `0x2B8` | `active` |

Together these functions outline a small lifecycle:

```mermaid
flowchart LR
    A["initialize shared loader"] --> B["clear/init state"]
    B --> C["compute aligned destination"]
    C --> D["load asset into destination"]
    D --> E["finalize/use payload"]
    E --> F["release active payload"]
```

## Why this matters

This slice is useful because it moves GT Mode recovery from anonymous leaves toward recognizable formats and lifecycles:

- compact records;
- relative-offset asset tables;
- a reusable loader state object.

Those are exactly the kinds of local concepts that make later dealership, garage, and menu recovery less opaque while preserving the original control flow.
