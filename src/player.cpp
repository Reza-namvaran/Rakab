#include "Player.hpp"

Player::Player(const std::string& p_name, const unsigned int& p_age){
  this->setPlayerName(p_name);
  this->setPlayerAge(p_age);
}

void Player::setPlayerName(const std::string& p_name){
  if(p_name != " " || p_name != "\n")
    this->name = p_name;
  else
    std::cerr << "Please enter a valid name!" << std::endl;
}

void Player::setPlayerAge(const unsigned int& p_age){
   this->age = p_age;
}

void Player::setPlayerScore(const unsigned int& p_score){
  this->total_score = p_score;
}

std::string Player::getPlayerName() const{
  return this->name;
}

unsigned int Player::getPlayerAge() const{
  return this->age;
}

unsigned int Player::getPlayerScore() const { return this->total_score; }

std::vector<Card> Player::getPlayerCards() const { return this->cards; }

Card* Player::selectCard(const Card& p_card){
  for(const auto& card : this->cards)
  {
    if(card.getCardName() == p_card.getCardName())
    {
      //return card;
      /// FATAL: fix this bug
    }
  }
  /// IMPORTANT: Add exception handling
}
