#include "mod1.hpp"

static std::shared_ptr<std::stringstream> out;

// implementation fo methods loaded from main-program
extern "C" {
size_t _IDENT_ = 50;

Interface *_CREATE_() { return new InterfaceMod1(); }
void _DESTROY_(Interface *interface) { delete interface; }
void _SET_OUT_(std::shared_ptr<std::stringstream> os) { out = os; }
}

InterfaceMod1::InterfaceMod1() {}

InterfaceMod1::~InterfaceMod1() {}

void InterfaceMod1::onCreate() {
  (*out) << "Created Mod1 Interface" << std::endl;
}

void InterfaceMod1::onUpdate(std::chrono::nanoseconds deltaTime) {
  (*out) << "Updated Mod1 Interface with dt of " << deltaTime.count() << "ns"
         << std::endl;
}

void InterfaceMod1::onDelete() {
  (*out) << "Deleted Mod1 Interface" << std::endl;
}
