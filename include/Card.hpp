#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <unordered_set>
#include "Player.hpp"
#include "IO_Interface.hpp"

class Card
{
protected:
  std::string name;
  std::string description;

public:
  Card(const std::string p_name);

  virtual ~Card() = default;

  virtual void use(std::unordered_set<Card *> &hand_cards, std::unordered_set<Card *> &player_cards, Player &player, IO_Interface &terminal_handler) = 0;

  virtual std::string getCardType() const = 0;

  std::string getCardName() const;

  void Card::setCardDescription(std::string description);

  std::string getCardDescription() const;
};

#endif
