#include "main.hpp"
#include <memory>
namespace fs = std::filesystem;

// flag to control input and lifecycle thread
std::atomic<bool> run;
// switch to update modules on command (maybe use more sufisticated method)
std::atomic<bool> update;

// output queue for modules (maybe replaced with SYSLOG)
std::deque<std::string> messageQueue;
std::mutex messageMutex;

int main(int argc, char *argv[]) {
  run = true;
  update = false;

  std::cout << "Welcome to this cpp modules example. To keep it simple you can "
               "only trigger a module update (u) or quit (q) the program.\n"
            << std::endl;

  std::thread input(&inputThread);
  std::thread lifecycle(&lifecycleThread);

  while (run) {
    // output loop for all modules
    // modules push output and this loop writes it to stdout
    messageMutex.lock();
    while (!messageQueue.empty()) {
      std::string message = messageQueue.front();
      std::cout << message;
      messageQueue.pop_front();
    }
    messageMutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  input.join();
  lifecycle.join();

  // check one last time for messages from modules
  while (!messageQueue.empty()) {
    std::string message = messageQueue.front();
    std::cout << message;
    messageQueue.pop_front();
  }

  return 0;
}

void inputThread() {
  std::string input;
  while (run) {
    std::cin >> input;
    std::transform(input.begin(), input.end(), input.begin(),
                   [](char c) -> char { return std::tolower(c); });

    if (input == "q" || input == "quit") {
      run = false;
    }

    if (input == "u" || input == "update") {
      update = true;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

// thread handling module lifecycles
void lifecycleThread() {
  // vector containing all viable modules
  std::vector<std::shared_ptr<Module>> modules;
  // shared pointer on stringstream that modules use for output
  std::shared_ptr<std::stringstream> modulesOut =
      std::make_shared<std::stringstream>();

  // definition of named lambda for handling output queue
  auto updateMessageQueue = [&modulesOut]() {
    std::string message = modulesOut->str();

    messageMutex.lock();
    messageQueue.push_back(message);
    messageMutex.unlock();

    modulesOut->str(std::string());
  };

  fs::path modules_dir = "modules";
  if (fs::exists(modules_dir)) {
    (*modulesOut) << "Reading modules from directory: "
                  << fs::absolute(modules_dir) << std::endl;
    updateMessageQueue();

    for (auto &file : fs::directory_iterator(modules_dir)) {
      // check whether this file is a viable dynamic lib
      if (file.is_regular_file() && file.file_size() > 0 &&
          file.path().extension().string().find(".so") >= 0) {

        // load dynamic lib into memory
        auto handle =
            dlopen(fs::absolute(file.path()).string().c_str(), RTLD_LAZY);

        // load variable _IDNET_ to make sure, this file is trustworthy
        size_t *identifier = (size_t *)dlsym(handle, "_IDENT_");
        // use more sophisticated method
        if (*identifier % 5 != 0) {
          (*modulesOut) << "Am not going to load lib: " << file.path()
                        << " because Identifier '" << *identifier
                        << "' does not match" << std::endl;
          dlclose(handle);
          continue;
        }

        // create module
        std::shared_ptr<Module> module = std::make_shared<Module>();
        module->handle = handle;
        module->identifier = *identifier;
        module->create = (createFun)dlsym(handle, "_CREATE_");
        module->destroy = (destroyFun)dlsym(handle, "_DESTROY_");
        module->setOut = (setOutFun)dlsym(handle, "_SET_OUT_");
        module->setOut(modulesOut);

        // instantiate interface implementation from module
        module->interface = std::shared_ptr<Interface>(
            module->create(), [](Interface *interface) {});

        // call modules onCreate method
        module->interface->onCreate();
        updateMessageQueue();

        modules.push_back(module);

        (*modulesOut) << "Loaded lib: " << file.path() << std::endl;
        updateMessageQueue();
      }
    }
  }

  auto then = std::chrono::steady_clock::now();
  // main loop of lifecycle thread
  while (run) {
    // update if flag is set
    if (update) {
      // measure dt
      auto now = std::chrono::steady_clock::now();
      auto deltaTime = now - then;
      // call onUpdate methods from all module's interface implementation
      for (auto &module : modules) {
        module->interface->onUpdate(deltaTime);
        updateMessageQueue();
      }
      update = false;
      then = now;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  // clear modules method from all module's interface implementation
  for (auto &module : modules) {
    module->interface->onDelete();
    module->destroy(module->interface.get());
    updateMessageQueue();
    dlclose(module->handle);
  }
}
