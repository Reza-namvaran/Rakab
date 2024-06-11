#include "Card.hpp"

Card::Card(const std::string p_name, const std::string p_description){
  this->name = p_name;
  this->description = p_description;
}

std::string Card::getCardName() const { return this->name; }

std::string Card::getCardDescription() const { return this->description; }
