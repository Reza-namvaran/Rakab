#include "Player.hpp"
#include "Card.hpp"
#include "PlayerSign.hpp"
#include <memory> // For std::shared_ptr

Player::Player(const std::string &p_name, const unsigned int &p_age)
    : name(p_name), age(p_age), total_score(0), sign(nullptr) {}

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

void Player::setPlayerPassed(const bool passed)
{
    this->passed = passed;
}

std::string Player::getPlayerName() const
{
    return this->name;
}

unsigned int Player::getPlayerAge() const
{
    return this->age;
}

unsigned int Player::getPlayerScore() const
{
    return this->total_score;
}

unsigned int Player::getPlayerLandsCount() const
{
    if (sign)
    {
        return this->sign->getLands().size();
    }
    return 0; // If the sign is not set, return 0
}

bool Player::getPlayerPassed() const { return this->passed; }

std::shared_ptr<PlayerSign> Player::getSign() const { return this->sign; }

std::vector<std::shared_ptr<Card>> Player::getCard(bool hand) const
{
    if (hand)
    {
        return this->hand;
    }
    else
    {
        return this->played;
    }
}

void Player::addCard(const std::vector<std::shared_ptr<Card>> &cards, bool toHand)
{
    if (toHand)
    {
        this->hand = cards;
    }
    else
    {
        this->played = cards;
    }
}

void Player::addLand(std::shared_ptr<Land> land)
{
    this->sign->setLand(land);
}

void Player::clearPlayedCard()
{
    this->played.clear();
}

std::shared_ptr<Card> Player::selectCard(const std::string &p_card)
{
    // TODO: Implement this method
    return nullptr;
}

void Player::playCard(std::string cardName)
{
    for (int i = 0; i < this->hand.size(); i++)
    {
        if (this->hand[i]->getCardName() == cardName)
        {
            this->played.emplace_back(this->hand[i]);
            this->hand.erase(this->hand.begin() + i);
            break;
        }
    }
}