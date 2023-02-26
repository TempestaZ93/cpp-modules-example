#pragma once

#include "interface.hpp"
#include <memory>
#include <sstream>

#include <iostream>

class InterfaceMod2 : public Interface {
public:
  InterfaceMod2();
  virtual ~InterfaceMod2() override;

  virtual void onCreate() override;
  virtual void onUpdate(std::chrono::nanoseconds deltaTime) override;
  virtual void onDelete() override;
};
