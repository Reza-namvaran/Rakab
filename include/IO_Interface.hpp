#ifndef IO_INTERFACE_H
#define IO_INTERFACE_H

#include <iostream>

#ifdef _WIN32
  #include <conio.h>

#else
  #include <ncurses>

#endif

class IO_Interface{
  public:
    IO_Interface();

    ~IO_Interface();

    /// NOTE: using template functions to avoid code repetition 
    template <typename T>
    void print(const T& p_data){
      std::cout << p_data << "\n";
    }

    template <typename T>
    void input(T& p_data){
      std::getline(std::cin, p_data);
    }

    void onClickInput() const;

    void clearScreen() const;
};

#endif // IO_INTERFACE_H
