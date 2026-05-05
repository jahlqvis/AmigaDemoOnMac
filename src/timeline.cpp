#include "timeline.hpp"

#include <algorithm>

namespace {

struct Keyframe {
  float time;
  float plasma;
  float fire;
  float copper;
  float starfield;
  float pentagram;
  float scroller;
  float rotationSpeed;
};

constexpr int kNumKeyframes = 13;

const Keyframe kKeyframes[kNumKeyframes] = {
  //  time   plasma fire  copper star  pent  scroll speed
  {   0.0f,  0.0,   0.0,  0.0,   1.0,  0.3,  1.0,   0.6  }, // intro
  {   8.0f,  0.0,   0.0,  0.0,   1.0,  0.3,  1.0,   0.6  },
  {   9.0f,  0.0,   0.0,  1.0,   0.5,  0.5,  1.0,   0.7  }, // copper in
  {  16.0f,  0.0,   0.0,  1.0,   0.5,  0.5,  1.0,   0.8  },
  {  17.0f,  1.0,   0.0,  0.3,   0.3,  0.7,  1.0,   1.0  }, // plasma in
  {  24.0f,  1.0,   0.0,  0.3,   0.3,  0.7,  1.0,   1.0  },
  {  25.0f,  0.4,   1.0,  0.0,   0.2,  1.0,  1.0,   1.3  }, // fire in
  {  34.0f,  0.4,   1.0,  0.0,   0.2,  1.0,  1.0,   1.5  },
  {  35.0f,  0.6,   1.0,  0.5,   0.4,  1.0,  1.0,   2.0  }, // finale: copper back
  {  44.0f,  0.6,   1.0,  0.5,   0.4,  1.0,  1.0,   2.0  },
  {  46.0f,  0.6,   1.0,  0.5,   0.4,  1.0,  1.0,   2.0  },
  {  50.0f,  0.0,   0.0,  0.0,   1.0,  0.0,  1.0,   0.4  }, // fade out
  {  54.0f,  0.0,   0.0,  0.0,   1.0,  0.0,  1.0,   0.4  },
};

void applyKeyframe(DemoState& s, const Keyframe& kf) {
  s.plasma = kf.plasma;
  s.fire = kf.fire;
  s.copper = kf.copper;
  s.starfield = kf.starfield;
  s.pentagram = kf.pentagram;
  s.scroller = kf.scroller;
  s.rotationSpeed = kf.rotationSpeed;
}

void lerpKeyframe(DemoState& s, const Keyframe& a, const Keyframe& b, float frac) {
  s.plasma = a.plasma + frac * (b.plasma - a.plasma);
  s.fire = a.fire + frac * (b.fire - a.fire);
  s.copper = a.copper + frac * (b.copper - a.copper);
  s.starfield = a.starfield + frac * (b.starfield - a.starfield);
  s.pentagram = a.pentagram + frac * (b.pentagram - a.pentagram);
  s.scroller = a.scroller + frac * (b.scroller - a.scroller);
  s.rotationSpeed = a.rotationSpeed + frac * (b.rotationSpeed - a.rotationSpeed);
}

} // namespace

void Timeline::reset() {
  applyKeyframe(state_, kKeyframes[0]);
}

void Timeline::update(double musicTimeSeconds, double dtSeconds) {
  (void)dtSeconds;

  const float t = static_cast<float>(musicTimeSeconds);

  int i = 0;
  while (i + 1 < kNumKeyframes && kKeyframes[i + 1].time < t) {
    ++i;
  }

  if (i + 1 >= kNumKeyframes) {
    applyKeyframe(state_, kKeyframes[kNumKeyframes - 1]);
  } else {
    const Keyframe& a = kKeyframes[i];
    const Keyframe& b = kKeyframes[i + 1];
    float frac = (t - a.time) / (b.time - a.time);
    frac = std::clamp(frac, 0.0f, 1.0f);
    lerpKeyframe(state_, a, b, frac);
  }

  state_.flash *= 0.9f;
  if ((t > 12.0f && t < 12.2f) || (t > 24.0f && t < 24.2f) ||
      (t > 28.0f && t < 28.2f) || (t > 32.0f && t < 32.2f) ||
      (t > 36.0f && t < 36.2f) || (t > 40.0f && t < 40.2f) ||
      (t > 44.0f && t < 44.2f)) {
    state_.flash = 1.0f;
  }
}

const DemoState& Timeline::state() const {
  return state_;
}
