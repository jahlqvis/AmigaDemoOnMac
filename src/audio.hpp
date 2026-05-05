#pragma once

#include <SDL_mixer.h>

#include <string>

class Audio {
public:
  bool initialize();
  bool loadMusic(const std::string& path);
  bool loadMusicFromMemory(const unsigned char* data, unsigned int size);
  void playMusic();
  double musicTimeSeconds() const;
  void shutdown();

private:
  Mix_Music* music_ = nullptr;
  bool playing_ = false;
  Uint64 startTicks_ = 0;
};
