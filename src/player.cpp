#include "Player.hpp"

void Player::setPlayerName(const std::string& p_name){
  this->name = p_name;
}

void Player::setPlayerAge(const unsigned int& p_age){
  this->age = p_age;
}

std::string Player::getPlayerName() const { return this->name; }

unsigned int Player::getPlayerAge() const { return this->age; }

void Player::addCard(const std::unordered_set<Card*>& p_hand) {
  this->hand = p_hand;
  /// NOTE: this is because we don't add single cards 
}

/* Card* Player::selectCard(const std::string& p_card){
  /// TODO: Implement this method
}*/
