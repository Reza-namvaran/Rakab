#ifndef MATCH_H
#define MATCH_H

#include "Player.hpp"
#include "Card.hpp"
#include "IO_Interface.hpp"
#include "Land.hpp"
#include "Sign.hpp"

class Match{
  private:
    std::vector<Player> players;

  public:
    Match(std::vector<Player> p_players);

    ~Match(); 
};

#endif // MATCH_H
