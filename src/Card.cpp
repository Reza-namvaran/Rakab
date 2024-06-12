#include "Card.hpp"

Card::Card(const std::string p_name)
{
  this->name = p_name;
}

std::string Card::getCardName() const { return this->name; }

void Card::setCardDescription(std::string description)
{
  this->description = description;
}

std::string Card::getCardDescription() const { return this->description; }
