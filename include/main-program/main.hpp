#pragma once

#include "dlfcn.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <dlfcn.h>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <utility>
#include <vector>

#include "interface.hpp"
// Method heads for callback methods
// method called when creating instance of a module
typedef Interface *(*createFun)();
// method called when module gets destroyed
typedef void (*destroyFun)(Interface *);
// nethod gets called for setting output stream for modules
// this can be a stringstream or a file or...
typedef void (*setOutFun)(std::shared_ptr<std::stringstream>);

// abstract module with necessary callbacks
struct Module {
  void *handle;
  size_t identifier;

  std::function<Interface *(void)> create;
  std::function<void(Interface *)> destroy;
  std::function<void(std::shared_ptr<std::stringstream>)> setOut;

  std::shared_ptr<Interface> interface;
};

// forward declaration of thread functions
void inputThread();
void lifecycleThread();
