#pragma once
#include <chrono>

class Interface {
public:
  Interface() = default;
  virtual ~Interface() = default;

  virtual void onCreate() = 0;
  virtual void onUpdate(std::chrono::nanoseconds deltaTime) = 0;
  virtual void onDelete() = 0;
};
