#pragma once

#include "audio.hpp"
#include "renderer.hpp"
#include "timeline.hpp"

#include <SDL.h>

class App {
public:
  bool initialize();
  void run();
  void shutdown();

private:
  void processEvents();
  void update(double dtSeconds);
  void render();

  bool running_ = false;

  SDL_Window* window_ = nullptr;

  Renderer renderer_;
  Audio audio_;
  Timeline timeline_;
};
