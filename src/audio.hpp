#pragma once

#include <SDL_mixer.h>

#include <string>

class Audio {
public:
  bool initialize();
  bool loadMusic(const std::string& path);
  void playMusic();
  double musicTimeSeconds() const;
  void shutdown();

private:
  Mix_Music* music_ = nullptr;
  bool playing_ = false;
  Uint64 startTicks_ = 0;
};
