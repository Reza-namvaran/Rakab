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
    void print(const T& p_data, const bool& new_line = true){
      if(new_line)
        std::cout << p_data << "\n";
      else
        std::cout << p_data << " ";
    }

    template <typename T>
    void input(T& p_data){
      std::getline(std::cin, p_data);
    }

    void onClickInput() const;

    void clearScreen() const;
};

#endif // IO_INTERFACE_H
