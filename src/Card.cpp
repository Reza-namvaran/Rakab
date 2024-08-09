#include "Card.hpp"

Card::Card(const std::string p_name, const char *cardPicPath)
{
  this->name = p_name;
  this->cardPic = LoadTexture(cardPicPath);
}

Card::Card(const std::string p_name)
{
  this->name = p_name;
}

Card::~Card()
{
  UnloadTexture(this->getCardPic());
}

std::string Card::getCardName() const { return this->name; }

Texture2D Card::getCardPic() const { return this->cardPic; }

void Card::setCardPic(const char *cardPicPath)
{
  this->cardPic = LoadTexture(cardPicPath);
}