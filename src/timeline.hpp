#pragma once

struct DemoState {
  float plasma = 0.0f;
  float fire = 0.0f;
  float copper = 0.0f;
  float starfield = 1.0f;
  float pentagram = 0.3f;
  float scroller = 1.0f;
  float flash = 0.0f;
  float rotationSpeed = 0.6f;
};

class Timeline {
public:
  void reset();
  void update(double musicTimeSeconds, double dtSeconds);
  const DemoState& state() const;

private:
  DemoState state_;
};
