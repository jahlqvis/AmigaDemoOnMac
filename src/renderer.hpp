#pragma once

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

  float objectAngle_ = 0.0f;
  float sceneBlend_ = 0.0f;
  float flash_ = 0.0f;
  float rotationSpeed_ = 0.6f;
};
