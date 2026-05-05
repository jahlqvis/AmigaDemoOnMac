#pragma once

#include <SDL.h>

class Scroller {
public:
  static constexpr int kCharStride = 8;

  void reset(const char* text);
  void update(double dtSeconds, float speed);
  void render(SDL_Renderer* renderer, int screenW, int screenH) const;

private:
  void drawChar(SDL_Renderer* renderer, char c, int x, int y) const;

  const char* text_ = nullptr;
  int textLen_ = 0;
  float pos_ = 0.0f;
  float time_ = 0.0f;
};
