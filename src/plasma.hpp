#pragma once

#include <SDL.h>

class Plasma {
public:
  bool initialize(SDL_Renderer* renderer, int w, int h);
  void update(double dtSeconds);
  void render(SDL_Renderer* renderer) const;
  SDL_Texture* texture() const { return texture_; }
  void shutdown();

private:
  SDL_Texture* texture_ = nullptr;
  int w_ = 0;
  int h_ = 0;
  float time_ = 0.0f;
  Uint32 palette_[256];
};
