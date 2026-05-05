#include "copper.hpp"

#include <cmath>

void CopperBars::reset() {
  time_ = 0.0f;
}

void CopperBars::update(double dtSeconds) {
  time_ += static_cast<float>(dtSeconds);
}

void CopperBars::render(SDL_Renderer* renderer, int w, int h, Uint8 alpha) const {
  for (int y = 0; y < h; ++y) {
    const float t = static_cast<float>(y) / static_cast<float>(h);

    const float r = std::sin(t * 10.0f + time_ * 1.5f) * 0.5f + 0.5f;
    const float g = std::sin(t * 14.0f + time_ * 2.2f + 2.0f) * 0.5f + 0.5f;
    const float b = std::sin(t * 8.0f + time_ * 0.9f + 4.0f) * 0.5f + 0.5f;

    const float rm = std::sin(t * 22.0f + time_ * 3.0f) * 0.3f + 0.3f;
    const float gm = std::sin(t * 18.0f + time_ * 2.7f + 1.5f) * 0.3f + 0.3f;
    const float bm = std::sin(t * 26.0f + time_ * 3.3f + 3.0f) * 0.3f + 0.3f;

    const Uint8 cr = static_cast<Uint8>((r + rm) * 180.0f);
    const Uint8 cg = static_cast<Uint8>((g + gm) * 160.0f);
    const Uint8 cb = static_cast<Uint8>((b + bm) * 200.0f);

    SDL_SetRenderDrawColor(renderer, cr, cg, cb, alpha);
    SDL_RenderDrawLine(renderer, 0, y, w - 1, y);
  }
}
