#include "fire.hpp"

#include <cstdlib>

bool Fire::initialize(SDL_Renderer* renderer, int w, int h) {
  w_ = w;
  h_ = h;

  texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING, w_, h_);
  if (!texture_) return false;

  SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);

  buffer_ = new uint8_t[w_ * h_];
  for (int i = 0; i < w_ * h_; ++i) {
    buffer_[i] = 0;
  }

  for (int i = 0; i < 256; ++i) {
    Uint8 r = 0, g = 0, b = 0;
    if (i < 32) {
      r = 0; g = 0; b = 0;
    } else if (i < 64) {
      r = static_cast<Uint8>(i * 2);
    } else if (i < 96) {
      r = static_cast<Uint8>(192 + (i - 64));
    } else if (i < 128) {
      r = 255;
      g = static_cast<Uint8>((i - 96) * 8);
    } else if (i < 160) {
      r = 255; g = 255;
      b = static_cast<Uint8>((i - 128) * 4);
    } else if (i < 192) {
      r = 255; g = 255; b = static_cast<Uint8>(128 + (i - 160) * 2);
    } else {
      r = 255; g = 255; b = 255;
    }
    Uint8 a = (i > 0) ? 255 : 0;
    palette_[i] = (a << 24) | (r << 16) | (g << 8) | b;
  }

  return true;
}

void Fire::update(double dtSeconds) {
  (void)dtSeconds;

  for (int y = 0; y < h_ - 1; ++y) {
    for (int x = 0; x < w_; ++x) {
      int xl = (x - 1 + w_) % w_;
      int xr = (x + 1) % w_;

      int sum = buffer_[(y + 1) * w_ + xl];
      sum += buffer_[(y + 1) * w_ + x];
      sum += buffer_[(y + 1) * w_ + xr];

      if (y + 2 < h_) {
        sum += buffer_[(y + 2) * w_ + x];
        sum /= 4;
      } else {
        sum /= 3;
      }

      if (sum > 1) sum -= (rand() & 1);

      buffer_[y * w_ + x] = static_cast<uint8_t>(sum);
    }
  }

  for (int x = 0; x < w_; ++x) {
    buffer_[(h_ - 1) * w_ + x] = static_cast<uint8_t>(rand() % 128 + 128);
    if (h_ >= 2) {
      buffer_[(h_ - 2) * w_ + x] = static_cast<uint8_t>(rand() % 64 + 64);
    }
  }
}

void Fire::render(SDL_Renderer* renderer) const {
  void* rawPixels;
  int pitch;
  SDL_LockTexture(texture_, nullptr, &rawPixels, &pitch);
  Uint32* pixels = static_cast<Uint32*>(rawPixels);
  const int stride = pitch / 4;

  for (int y = 0; y < h_; ++y) {
    for (int x = 0; x < w_; ++x) {
      pixels[y * stride + x] = palette_[buffer_[y * w_ + x]];
    }
  }

  SDL_UnlockTexture(texture_);
  SDL_RenderCopy(renderer, texture_, nullptr, nullptr);
}

void Fire::shutdown() {
  if (texture_) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
  delete[] buffer_;
  buffer_ = nullptr;
}
