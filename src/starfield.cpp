#include "starfield.hpp"

#include <cstdlib>

namespace {

float frand() {
  return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

} // namespace

void Starfield::reset() {
  srand(42);
  for (int i = 0; i < kMaxStars; ++i) {
    stars_[i].x = frand() * 2.0f - 1.0f;
    stars_[i].y = frand() * 2.0f - 1.0f;
    stars_[i].z = frand();
  }
}

void Starfield::update(double dtSeconds, float speed) {
  const float dz = speed * static_cast<float>(dtSeconds);
  for (int i = 0; i < kMaxStars; ++i) {
    stars_[i].z -= dz;
    if (stars_[i].z <= 0.0f) {
      stars_[i].z += 1.0f;
      stars_[i].x = frand() * 2.0f - 1.0f;
      stars_[i].y = frand() * 2.0f - 1.0f;
    }
  }
}

void Starfield::render(SDL_Renderer* renderer, int screenW, int screenH) const {
  SDL_Point points[kMaxStars];
  int count = 0;
  const int cx = screenW / 2;
  const int cy = screenH / 2;

  for (int i = 0; i < kMaxStars; ++i) {
    if (stars_[i].z <= 0.0f) continue;

    const float invZ = 1.0f / stars_[i].z;
    const int sx = cx + static_cast<int>(stars_[i].x * invZ * static_cast<float>(cx));
    const int sy = cy + static_cast<int>(stars_[i].y * invZ * static_cast<float>(cy));

    if (sx >= 0 && sx < screenW && sy >= 0 && sy < screenH) {
      points[count].x = sx;
      points[count].y = sy;
      ++count;
    }
  }

  if (count > 0) {
    SDL_RenderDrawPoints(renderer, points, count);
  }
}
