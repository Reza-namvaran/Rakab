#include "Card.hpp"

std::string Card::getCardName() const { return this->name; }

std::string Card::getCardDescription() const { return this->description; }

unsigned int Card::getScore() const { return this->score; }

/// NOTE: added setter for cards that can change other cards score
/// TODO: Find a way to handle scores in game

void Card::setScore(const unsigned int& p_score){
  this->score = p_score;
}