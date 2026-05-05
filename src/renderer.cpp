#include "renderer.hpp"

#include <algorithm>
#include <cmath>

bool Renderer::initialize(SDL_Window* window) {
  window_ = window;
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer_) return false;

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

  targetTexture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_TARGET,
                                     kTargetWidth, kTargetHeight);
  if (!targetTexture_) return false;

  if (!plasma_.initialize(renderer_, kTargetWidth, kTargetHeight)) return false;
  if (!fire_.initialize(renderer_, kTargetWidth, kTargetHeight)) return false;

  starfield_.reset();
  copperBars_.reset();
  scroller_.reset("WELCOME TO THE AMIGA DEMO V1 -- CODED IN C++ WITH SDL2 -- GREETINGS TO THE DEMOSCENE -- "
                   "NOW WE ARE GOING TO ROCK YOUR AMIGA -- RESPECT TO ALL THE OLD SCHOOL CODERS -- "
                   "ENJOY THE SHOW -- ");
  return true;
}

void Renderer::update(const DemoState& state, double dtSeconds) {
  plasmaBlend_ = state.plasma;
  fireBlend_ = state.fire;
  copperBlend_ = state.copper;
  starfieldBlend_ = state.starfield;
  pentagramBlend_ = state.pentagram;
  scrollerBlend_ = state.scroller;
  flash_ = state.flash;
  rotationSpeed_ = state.rotationSpeed;

  plasma_.update(dtSeconds);
  fire_.update(dtSeconds);
  copperBars_.update(dtSeconds);
  starfield_.update(dtSeconds, rotationSpeed_ * 0.8f);
  scroller_.update(dtSeconds, rotationSpeed_ * 4.0f);

  objectAngle_ += static_cast<float>(dtSeconds) * rotationSpeed_;
  if (objectAngle_ > 6.2831853f) {
    objectAngle_ -= 6.2831853f;
  }
}

void Renderer::render() {
  SDL_SetRenderTarget(renderer_, targetTexture_);

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);

  if (plasmaBlend_ > 0.01f) {
    SDL_SetTextureAlphaMod(plasma_.texture(), static_cast<Uint8>(plasmaBlend_ * 255.0f));
    plasma_.render(renderer_);
  }

  if (copperBlend_ > 0.01f) {
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    const Uint8 ca = static_cast<Uint8>(copperBlend_ * 120.0f);
    copperBars_.render(renderer_, kTargetWidth, kTargetHeight, ca);
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_NONE);
  }

  if (fireBlend_ > 0.01f) {
    SDL_SetTextureAlphaMod(fire_.texture(), static_cast<Uint8>(fireBlend_ * 255.0f));
    fire_.render(renderer_);
  }

  if (starfieldBlend_ > 0.01f) {
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255,
                           static_cast<Uint8>(starfieldBlend_ * 255.0f));
    starfield_.render(renderer_, kTargetWidth, kTargetHeight);
  }

  if (pentagramBlend_ > 0.01f) {
    const float pulse = 0.5f + 0.5f * std::sin(objectAngle_ * 2.0f);

    const int cx = kTargetWidth / 2;
    const int cy = kTargetHeight / 2;
    const int size = 20 + static_cast<int>(25.0f * pentagramBlend_);

    SDL_Point poly[5];
    for (int i = 0; i < 5; ++i) {
      const float a = objectAngle_ + static_cast<float>(i) * (6.2831853f / 5.0f);
      const float r = static_cast<float>(size) * (0.75f + 0.25f * ((i % 2 == 0) ? 1.0f : 0.6f));
      poly[i].x = cx + static_cast<int>(std::cos(a) * r);
      poly[i].y = cy + static_cast<int>(std::sin(a) * r);
    }

    const Uint8 objR = static_cast<Uint8>(130.0f + 80.0f * pulse);
    const Uint8 objG = static_cast<Uint8>(110.0f + 70.0f * pentagramBlend_);
    const Uint8 objB = static_cast<Uint8>(90.0f + 50.0f * (1.0f - pentagramBlend_));
    const Uint8 objA = static_cast<Uint8>(pentagramBlend_ * 255.0f);
    SDL_SetRenderDrawColor(renderer_, objR, objG, objB, objA);

    for (int i = 0; i < 5; ++i) {
      const int next = (i + 1) % 5;
      SDL_RenderDrawLine(renderer_, poly[i].x, poly[i].y, poly[next].x, poly[next].y);
      SDL_RenderDrawLine(renderer_, cx, cy, poly[i].x, poly[i].y);
    }
  }

  if (scrollerBlend_ > 0.01f) {
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255,
                           static_cast<Uint8>(scrollerBlend_ * 255.0f));
    scroller_.render(renderer_, kTargetWidth, kTargetHeight);
  }

  if (flash_ > 0.01f) {
    const Uint8 alpha = static_cast<Uint8>(std::clamp(flash_ * 120.0f, 0.0f, 120.0f));
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, alpha);
    SDL_Rect rect{0, 0, kTargetWidth, kTargetHeight};
    SDL_RenderFillRect(renderer_, &rect);
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_NONE);
  }

  SDL_SetRenderTarget(renderer_, nullptr);
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);

  int winW, winH;
  SDL_GetWindowSize(window_, &winW, &winH);

  const float scale = std::min(static_cast<float>(winW) / kTargetWidth,
                               static_cast<float>(winH) / kTargetHeight);
  const int dstW = static_cast<int>(kTargetWidth * scale);
  const int dstH = static_cast<int>(kTargetHeight * scale);
  SDL_Rect dstRect{(winW - dstW) / 2, (winH - dstH) / 2, dstW, dstH};

  SDL_RenderCopy(renderer_, targetTexture_, nullptr, &dstRect);
  SDL_RenderPresent(renderer_);
}

void Renderer::shutdown() {
  plasma_.shutdown();
  fire_.shutdown();

  if (targetTexture_) {
    SDL_DestroyTexture(targetTexture_);
    targetTexture_ = nullptr;
  }
  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }
}
