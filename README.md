# Amiga-Style Demo v1 (Skeleton)

Native macOS C++ skeleton for a retro demo with SDL2 + SDL2_mixer.

## Prerequisites

Install tools and libraries with Homebrew:

```bash
brew install cmake sdl2 sdl2_mixer
```

## Build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/amiga_demo
```

Controls:

- `Esc`: quit

## Assets

Put your music file at:

`assets/audio/demo.ogg`

If the file is missing, the app still runs but without music.
