#include "IO_Interface.hpp"

IO_Interface::IO_Interface() {}

IO_Interface::~IO_Interface() {}

void IO_Interface::onClickInput() const {
  #ifdef _WIN32
    char ch = getch();
  #else
/*     initscr(); // Initialize ncurses mode
    noecho();  // Do not echo the character
    cbreak();  // Disable line buffering

    int ch = getch();   // Wait for user input
    endwin(); // End ncurses mode */

  #endif
}

// This method is used for clearing consol screen in different operating systems
void IO_Interface::clearScreen() const {
  #ifdef _WIN32
    system("CLS");
  #else
    system("CLEAR");
  #endif
}
