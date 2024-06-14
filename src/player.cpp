#include "Player.hpp"
#include "Card.hpp"
#include "PlayerSign.hpp"

Player::Player(const std::string &p_name, const unsigned int &age) : name(p_name), age(age) {}

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

unsigned int Player::getPlayerLandsCount() const
{
  return this->sign->getLands().size();
}

std::vector<Card *> Player::getCard(bool hand) const
{
  if (hand)
    return this->hand;
  else
    return this->played;
}

void Player::addCard(const std::vector<Card *> &cards, bool toHand)
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
