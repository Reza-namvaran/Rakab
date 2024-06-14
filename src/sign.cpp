#include "Sign.hpp"

Sign::Sign() {}

Sign::Sign(const std::string &p_color)
{
  this->color = p_color;
}

void Sign::setOwner(Player *owner)
{
  this->owner = owner;
}

Player *Sign::getOwner() const { return this->owner; }