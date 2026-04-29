#pragma once

struct DemoState {
  float sceneBlend = 0.0f;
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
