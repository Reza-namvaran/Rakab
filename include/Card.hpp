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
  Texture2D cardPic;

public:
  Card(const std::string p_name, const char *cardPicPath);
  Card(const std::string p_name);
  virtual ~Card();

  virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) = 0;

  virtual std::string getCardType() const = 0;

  std::string getCardName() const;
  Texture2D getCardPic() const;
  void setCardPic(const char *cardPicPath);
};

#endif