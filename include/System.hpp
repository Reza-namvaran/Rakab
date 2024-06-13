#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <ctime>

#include "IO_Interface.hpp"
#include "Player.hpp"
#include "Match.hpp"

class System{
  private:
    IO_Interface terminal_handler;
    std::vector<Player> players;
  
  public:
    System();

    ~System();

    void initialize();

    void selectMatch(int match_id);
    
    void runMatch() const;     
};

#endif // SYSTEM_H
