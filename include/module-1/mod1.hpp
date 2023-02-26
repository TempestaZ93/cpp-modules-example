#pragma once

#include "interface.hpp"
#include <memory>
#include <sstream>

#include <iostream>

class InterfaceMod1 : public Interface {
public:
  InterfaceMod1();
  virtual ~InterfaceMod1() override;

  virtual void onCreate() override;
  virtual void onUpdate(std::chrono::nanoseconds deltaTime) override;
  virtual void onDelete() override;
};
