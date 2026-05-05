#include "audio.hpp"

#include <SDL.h>

#include <iostream>

bool Audio::initialize() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
    std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << "\n";
    return false;
  }

  const int flags = MIX_INIT_OGG;
  const int initializedFlags = Mix_Init(flags);
  if ((initializedFlags & flags) != flags) {
    std::cerr << "Mix_Init OGG failed: " << Mix_GetError() << "\n";
    return false;
  }

  return true;
}

bool Audio::loadMusic(const std::string& path) {
  if (music_) {
    Mix_FreeMusic(music_);
    music_ = nullptr;
  }

  music_ = Mix_LoadMUS(path.c_str());
  return music_ != nullptr;
}

bool Audio::loadMusicFromMemory(const unsigned char* data, unsigned int size) {
  if (music_) {
    Mix_FreeMusic(music_);
    music_ = nullptr;
  }

  SDL_RWops* rw = SDL_RWFromConstMem(data, static_cast<int>(size));
  if (!rw) return false;

  music_ = Mix_LoadMUS_RW(rw, 1);
  return music_ != nullptr;
}

void Audio::playMusic() {
  if (!music_) {
    return;
  }

  if (Mix_PlayMusic(music_, 0) != 0) {
    std::cerr << "Mix_PlayMusic failed: " << Mix_GetError() << "\n";
    return;
  }

  playing_ = true;
  startTicks_ = SDL_GetPerformanceCounter();
}

double Audio::musicTimeSeconds() const {
  if (!playing_) {
    return 0.0;
  }

  const Uint64 now = SDL_GetPerformanceCounter();
  const double frequency = static_cast<double>(SDL_GetPerformanceFrequency());
  return static_cast<double>(now - startTicks_) / frequency;
}

void Audio::shutdown() {
  if (music_) {
    Mix_FreeMusic(music_);
    music_ = nullptr;
  }

  Mix_CloseAudio();
  Mix_Quit();
}
