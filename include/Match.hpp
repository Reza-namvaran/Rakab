#ifndef MATCH_H
#define MATCH_H

#include "Player.hpp"
#include "Card.hpp"
#include "CardDeck.hpp"
#include "IO_Interface.hpp"
#include "Land.hpp"
#include "Sign.hpp"

class Match{
  private:
    IO_Interface terminal_handler;
    std::vector<Player> players;
    bool is_match_over = false;

  public:
    Match(std::vector<Player> p_players);

    ~Match();

    int findRoundStarter(bool first_round);

    void run();
};

#endif // MATCH_H
