#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

#include "IO_Interface.hpp"
#include "Player.hpp"

class System{
  private:
    IO_Interface terminal_handler;
    unsigned int player_count;
    std::vector <Player> players;
  
  public:
    System();

    ~System();

    void initialize();

    void runMatch() const;     
};

#endif // SYSTEM_H
