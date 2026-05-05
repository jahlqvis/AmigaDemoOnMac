#include "app.hpp"
#include "demo_ogg.h"

#include <SDL.h>

#include <iostream>

namespace {
constexpr int kWindowWidth = 960;
constexpr int kWindowHeight = 768;
constexpr const char* kWindowTitle = "Amiga Demo v1";
} // namespace

bool App::initialize() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
    return false;
  }

  window_ = SDL_CreateWindow(
    kWindowTitle,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    kWindowWidth,
    kWindowHeight,
    SDL_WINDOW_SHOWN
  );

  if (!window_) {
    std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
    return false;
  }

  if (!renderer_.initialize(window_)) {
    return false;
  }

  if (!audio_.initialize()) {
    return false;
  }

  if (!audio_.loadMusicFromMemory(assets_audio_demo_ogg, assets_audio_demo_ogg_len)) {
    std::cerr << "Warning: could not load embedded music; running without music\n";
  } else {
    audio_.playMusic();
  }

  timeline_.reset();
  running_ = true;
  return true;
}

void App::run() {
  Uint64 previousCounter = SDL_GetPerformanceCounter();
  const double frequency = static_cast<double>(SDL_GetPerformanceFrequency());

  while (running_) {
    processEvents();

    const Uint64 now = SDL_GetPerformanceCounter();
    const double dtSeconds = static_cast<double>(now - previousCounter) / frequency;
    previousCounter = now;

    update(dtSeconds);
    render();
  }
}

void App::shutdown() {
  audio_.shutdown();
  renderer_.shutdown();

  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }

  SDL_Quit();
}

void App::processEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event) == 1) {
    if (event.type == SDL_QUIT) {
      running_ = false;
    }

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
      running_ = false;
    }
  }
}

void App::update(double dtSeconds) {
  const double musicTime = audio_.musicTimeSeconds();
  timeline_.update(musicTime, dtSeconds);
  renderer_.update(timeline_.state(), dtSeconds);
}

void App::render() {
  renderer_.render();
}
