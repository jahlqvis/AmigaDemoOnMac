#pragma once

#include "copper.hpp"
#include "fire.hpp"
#include "plasma.hpp"
#include "scroller.hpp"
#include "starfield.hpp"
#include "timeline.hpp"

#include <SDL.h>

class Renderer {
public:
  static constexpr int kTargetWidth = 320;
  static constexpr int kTargetHeight = 256;

  bool initialize(SDL_Window* window);
  void update(const DemoState& state, double dtSeconds);
  void render();
  void shutdown();

private:
  SDL_Renderer* renderer_ = nullptr;
  SDL_Window* window_ = nullptr;
  SDL_Texture* targetTexture_ = nullptr;

  Plasma plasma_;
  Fire fire_;
  CopperBars copperBars_;
  Starfield starfield_;
  Scroller scroller_;

  float objectAngle_ = 0.0f;

  float plasmaBlend_ = 0.0f;
  float fireBlend_ = 0.0f;
  float copperBlend_ = 0.0f;
  float starfieldBlend_ = 1.0f;
  float pentagramBlend_ = 0.3f;
  float scrollerBlend_ = 1.0f;
  float flash_ = 0.0f;
  float rotationSpeed_ = 0.6f;
};
