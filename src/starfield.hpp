#pragma once

#include <SDL.h>

class Starfield {
public:
  static constexpr int kMaxStars = 200;

  void reset();
  void update(double dtSeconds, float speed);
  void render(SDL_Renderer* renderer, int screenW, int screenH) const;

private:
  struct Star {
    float x, y, z;
  };
  Star stars_[kMaxStars];
};
