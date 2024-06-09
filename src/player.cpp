#include "Player.hpp"

void Player::setPlayerName(const std::string& p_name){
  this->name = p_name;
}

void Player::setPlayerAge(const unsigned int& p_age){
  this->age = p_age;
}

std::string Player::getPlayerName() const { return this->name; }

unsigned int Player::getPlayerAge() const { return this->age; }

// unsigned int Player::getPlayerScore() const { return this->total_score; }

std::vector<Card*> Player::getPlayerCards() const { return this->cards; }

Card* Player::selectCard(){
  
}
