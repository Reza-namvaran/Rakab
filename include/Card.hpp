#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>
#include <memory>

#include "IO_Interface.hpp"
#include "Player.hpp"

class Player;

class Card
{
protected:
  std::string name;
  std::string description;

public:
  Card(const std::string p_name);

  virtual ~Card() = default;

  virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) = 0;

  virtual std::string getCardType() const = 0;

  std::string getCardName() const;

  void setCardDescription(std::string description);

  std::string getCardDescription() const;
};

#endif