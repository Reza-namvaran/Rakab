#ifndef MATCH_H
#define MATCH_H

#include "Player.hpp"
#include "Card.hpp"
#include "CardDeck.hpp"
#include "IO_Interface.hpp"
#include "Land.hpp"
#include "WarSign.hpp"
#include <memory>

class Match {
private:
    IO_Interface terminal_handler;
    std::vector<std::shared_ptr<Player>> players;
    bool is_match_over = false;
    std::shared_ptr<CardDeck> deck;
    std::shared_ptr<WarSign> warSign;

public:
   Match(std::vector<std::shared_ptr<Player>> p_players);

   ~Match();

   void dealCard();

   void rechargeDeck();

   void run();
};

#endif // MATCH_H