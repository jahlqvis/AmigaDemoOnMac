#include "plasma.hpp"

#include <cmath>
#include <cstdint>

bool Plasma::initialize(SDL_Renderer* renderer, int w, int h) {
  w_ = w;
  h_ = h;
  time_ = 0.0f;

  texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING, w_, h_);
  if (!texture_) return false;

  for (int i = 0; i < 256; ++i) {
    const float t = static_cast<float>(i) / 256.0f;
    const Uint8 r = static_cast<Uint8>((std::sin(t * 6.2831f + 0.0f) * 0.5f + 0.5f) * 255.0f);
    const Uint8 g = static_cast<Uint8>((std::sin(t * 6.2831f + 2.094f) * 0.5f + 0.5f) * 255.0f);
    const Uint8 b = static_cast<Uint8>((std::sin(t * 6.2831f + 4.189f) * 0.5f + 0.5f) * 255.0f);
    palette_[i] = (255u << 24) | (r << 16) | (g << 8) | b;
  }

  return true;
}

void Plasma::update(double dtSeconds) {
  time_ += static_cast<float>(dtSeconds);
}

void Plasma::render(SDL_Renderer* renderer) const {
  void* rawPixels;
  int pitch;
  SDL_LockTexture(texture_, nullptr, &rawPixels, &pitch);
  Uint32* pixels = static_cast<Uint32*>(rawPixels);
  const int stride = pitch / 4;

  const float cx1 = static_cast<float>(w_) * 0.5f;
  const float cy1 = static_cast<float>(h_) * 0.5f;
  const float cx2 = static_cast<float>(w_) * 0.35f;
  const float cy2 = static_cast<float>(h_) * 0.65f;
  const float cx3 = static_cast<float>(w_) * 0.65f;
  const float cy3 = static_cast<float>(h_) * 0.35f;

  for (int y = 0; y < h_; ++y) {
    const float fy = static_cast<float>(y);
    for (int x = 0; x < w_; ++x) {
      const float fx = static_cast<float>(x);

      float v = 0.0f;
      v += std::sin(fx * 0.045f + time_ * 0.7f);
      v += std::sin(fy * 0.055f + time_ * 0.9f);
      v += std::sin((fx + fy) * 0.035f + time_ * 1.1f);
      v += std::sin(std::sqrt((fx - cx1) * (fx - cx1) + (fy - cy1) * (fy - cy1)) * 0.035f + time_ * 1.3f);
      v += std::sin(std::sqrt((fx - cx2) * (fx - cx2) + (fy - cy2) * (fy - cy2)) * 0.04f + time_ * 0.5f);
      v += std::sin(std::sqrt((fx - cx3) * (fx - cx3) + (fy - cy3) * (fy - cy3)) * 0.045f + time_ * 0.8f);

      const Uint8 idx = static_cast<Uint8>((v + 6.0f) * 21.0f);
      pixels[y * stride + x] = palette_[idx];
    }
  }

  SDL_UnlockTexture(texture_);
  SDL_RenderCopy(renderer, texture_, nullptr, nullptr);
}

void Plasma::shutdown() {
  if (texture_) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
}
