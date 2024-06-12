#ifndef IO_INTERFACE_H
#define IO_INTERFACE_H

#include <iostream>

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
      std::cin >> p_data;

      /// IMPORTANT: Decide on using getline()
    }
};

#endif // IO_INTERFACE_H