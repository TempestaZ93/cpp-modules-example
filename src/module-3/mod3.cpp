#include "mod3.hpp"

static std::shared_ptr<std::stringstream> out;

// implementation fo methods loaded from main-program
extern "C" {
    // this ident is wrong on purpose and leads to this module not being loaded
    // in case you want it to work, change it to a multuple of 5
size_t _IDENT_ = 31;

Interface *_CREATE_() { return new InterfaceMod3(); }
void _DESTROY_(Interface *interface) { delete interface; }
void _SET_OUT_(std::shared_ptr<std::stringstream> os) { out = os; }
}

InterfaceMod3::InterfaceMod3() {}

InterfaceMod3::~InterfaceMod3() {}

void InterfaceMod3::onCreate() {
  (*out) << "Created Mod3 Interface" << std::endl;
}

void InterfaceMod3::onUpdate(std::chrono::nanoseconds deltaTime) {
  (*out) << "Updated Mod3 Interface with dt of " << deltaTime.count() << "ns"
         << std::endl;
}

void InterfaceMod3::onDelete() {
  (*out) << "Deleted Mod3 Interface" << std::endl;
}
