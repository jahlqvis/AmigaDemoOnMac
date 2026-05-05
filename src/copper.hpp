#pragma once

#include <SDL.h>

class CopperBars {
public:
  void reset();
  void update(double dtSeconds);
  void render(SDL_Renderer* renderer, int screenW, int screenH, Uint8 alpha = 255) const;

private:
  float time_ = 0.0f;
};
