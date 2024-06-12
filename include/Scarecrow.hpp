#ifndef SCARECROW_H
#define SCARECROW_H

#include "Special.hpp"

class Scarecrow : public Special
{
public:
  Scarecrow(const std::string p_name);

  virtual void use(std::unordered_set<Card *> &hand_cards, std::unordered_set<Card *> &player_cards, Player &player, IO_Interface &terminal_handler) override;
};

#endif // SCARECROW_H
