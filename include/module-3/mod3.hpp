#pragma once

#include "interface.hpp"
#include <memory>
#include <sstream>

#include <iostream>

class InterfaceMod3 : public Interface {
public:
  InterfaceMod3();
  virtual ~InterfaceMod3() override;

  virtual void onCreate() override;
  virtual void onUpdate(std::chrono::nanoseconds deltaTime) override;
  virtual void onDelete() override;
};
