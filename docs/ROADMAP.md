# Roadmap

## Milestone 0 — Foundation

- Adopt and preserve the upstream decompilation base.
- Ingest vanilla and structurally compatible modified US 1.2 Simulation discs.
- Keep extracted content out of Git and generate deterministic manifests.
- Establish public contracts for runtime profiles and future resource packs.

## Milestone 1 — Faithful Simulation Mode core

- Complete the code paths required for boot, menus, GT Mode progression, garage, dealerships, licenses, racing, and saves.
- Keep behavior validation against the original game as the acceptance bar.
- Improve symbol quality, naming, structs, and overlay reconstruction as understanding grows.

## Milestone 2 — Native host prototype

- Introduce the host/platform boundary around the faithful core.
- Target Windows first, with controller support from the start.
- Implement `enhanced` and `original` runtime profiles against the same core logic.

## Milestone 3 — Content compatibility

- Treat patched user discs such as Project A-Spec as first-class supported inputs.
- Add resource-pack loading sufficient for a PAL translation import experiment.
- Keep Arcade Disc, full PAL executable support, and a broader mod ecosystem outside the critical path until Simulation Mode is stable.
