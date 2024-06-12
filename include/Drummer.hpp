#ifndef DRUMMER_H
#define DRUMMER_H

#include "Special.hpp"

class Drummer : public Special
{
public:
  Drummer(const std::string p_name);

  virtual void use(std::unordered_set<Card *> &hand_cards, std::unordered_set<Card *> &player_cards, Player &player, IO_Interface &terminal_handler) override;
};

#endif // DRUMMER_H
