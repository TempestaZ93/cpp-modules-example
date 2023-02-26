#include "mod2.hpp"

static std::shared_ptr<std::stringstream> out;

// implementation fo methods loaded from main-program
extern "C" {
size_t _IDENT_ = 25;

Interface *_CREATE_() { return new InterfaceMod2(); }
void _DESTROY_(Interface *interface) { delete interface; }
void _SET_OUT_(std::shared_ptr<std::stringstream> os) { out = os; }
}

InterfaceMod2::InterfaceMod2() {}

InterfaceMod2::~InterfaceMod2() {}

void InterfaceMod2::onCreate() {
  (*out) << "Created Mod2 Interface" << std::endl;
}

void InterfaceMod2::onUpdate(std::chrono::nanoseconds deltaTime) {
  (*out) << "Updated Mod2 Interface with dt of " << deltaTime.count() << "ns"
         << std::endl;
}

void InterfaceMod2::onDelete() {
  (*out) << "Deleted Mod2 Interface" << std::endl;
}
