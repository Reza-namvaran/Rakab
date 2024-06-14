#include "Player.hpp"
#include "Card.hpp"
#include "PlayerSign.hpp"
#include <memory> // For std::shared_ptr

Player::Player(const std::string &p_name, const unsigned int &p_age)
    : name(p_name), age(p_age), total_score(0), sign(nullptr) {}

void Player::setPlayerName(const std::string &p_name) {
    this->name = p_name;
}

void Player::setPlayerAge(const unsigned int &p_age) {
    this->age = p_age;
}

void Player::setPlayerScore(const unsigned int score) {
    this->total_score = score;
}

std::string Player::getPlayerName() const {
    return this->name;
}

unsigned int Player::getPlayerAge() const {
    return this->age;
}

unsigned int Player::getPlayerScore() const {
    return this->total_score;
}

unsigned int Player::getPlayerLandsCount() const {
    if (sign) {
        return this->sign->getLands().size();
    }
    return 0; // If the sign is not set, return 0
}

std::vector<std::shared_ptr<Card>> Player::getCard(bool hand) const {
    if (hand) {
        return this->hand;
    } else {
        return this->played;
    }
}

void Player::addCard(const std::vector<std::shared_ptr<Card>> &cards, bool toHand) {
    if (toHand) {
        this->hand = cards;
    } else {
        this->played = cards;
    }
}

void Player::clearPlayedCard() {
    this->played.clear();
}

std::shared_ptr<Card> Player::selectCard(const std::string &p_card) {
    // TODO: Implement this method
    return nullptr;
}