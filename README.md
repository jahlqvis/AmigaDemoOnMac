# Amiga Demo v1

Retro demoscene demo for macOS — single self-contained executable. 320×256 PAL resolution with nearest-neighbor upscaling, music-synced keyframe-driven scenes, and embedded OGG audio.

## Effects

- **Starfield** — 200-star 3D particle system
- **Copper bars** — per-scanline sine wave background
- **Plasma** — 6-component rainbow sine plasma
- **Fire** — procedural flame with custom palette
- **Pentagram** — rotating 5-pointed star with color pulse
- **Scroller** — sine wave text with embedded 8×8 bitmap font

## Scene Timeline

| Time | Scene | Active Effects |
|------|-------|---------------|
| 0–8s | Intro | Starfield, scroller, pentagram |
| 8–16s | Copper Dream | Copper fades in, starfield dims |
| 16–24s | Plasma Waves | Plasma in, copper overlay |
| 24–34s | Inferno | Fire in, copper out, flash bursts |
| 34–44s | Grand Finale | All effects layered, max speed |
| 44–54s | Outro | Fade to starfield |

## Prerequisites

```bash
brew install cmake sdl2 sdl2_mixer
```

## Build & Run

```bash
cmake -S . -B build
cmake --build build
./build/amiga_demo
```

## Controls

- `Esc` — quit

The demo is fully self-contained — music is embedded in the executable. No external files needed.
