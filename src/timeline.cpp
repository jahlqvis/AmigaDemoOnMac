#include "timeline.hpp"

#include <algorithm>

void Timeline::reset() {
  state_ = {};
}

void Timeline::update(double musicTimeSeconds, double dtSeconds) {
  (void)dtSeconds;

  const float t = static_cast<float>(musicTimeSeconds);

  state_.sceneBlend = std::clamp(t / 8.0f, 0.0f, 1.0f);

  state_.rotationSpeed = (t < 16.0f) ? 0.6f : 1.0f;

  state_.flash *= 0.9f;
  if ((t > 12.0f && t < 12.2f) || (t > 24.0f && t < 24.2f) || (t > 36.0f && t < 36.2f)) {
    state_.flash = 1.0f;
  }
}

const DemoState& Timeline::state() const {
  return state_;
}
