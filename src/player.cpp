#include "Player.hpp"

void Player::setPlayerName(const std::string &p_name)
{
  this->name = p_name;
}

void Player::setPlayerAge(const unsigned int &p_age)
{
  this->age = p_age;
}

void Player::setPlayerScore(const unsigned int score)
{
  this->total_score = score;
}

std::string Player::getPlayerName() const { return this->name; }

unsigned int Player::getPlayerAge() const { return this->age; }

unsigned int Player::getPlayerScore() const { return this->total_score; }

void Player::addCard(const std::unordered_set<Card *> &cards, bool toHand = true)
{
  if (toHand)
  {
    this->hand = cards;
  }
  else
  {
    this->played = cards;
  }

  /// NOTE: this is because we don't add single cards
}

void Player::clearPlayedCard()
{
  this->played.clear();
}

/* Card* Player::selectCard(const std::string& p_card){
  /// TODO: Implement this method
}*/
