#include "IO_Interface.hpp"

IO_Interface::IO_Interface() {}

IO_Interface::~IO_Interface() {}

// This method is used for clearing consol screen in different operating systems
void IO_Interface::clearScreen() const {
  #ifdef _WIN32
    system("CLS");
  #else
    system("CLEAR");
  #endif
}
