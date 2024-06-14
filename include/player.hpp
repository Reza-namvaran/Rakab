#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <memory>
#include "Land.hpp"

class Card;
class PlayerSign;

class Player
{
private:
    std::string name;
    unsigned int age;
    unsigned int total_score;
    bool passed = false;
    std::vector<std::shared_ptr<Card>> hand;
    std::vector<std::shared_ptr<Card>> played;
    std::shared_ptr<PlayerSign> sign;

public:
    Player(const std::string &p_name, const unsigned int &age);

    void setPlayerName(const std::string &p_name);
    void setPlayerAge(const unsigned int &p_age);
    void setPlayerScore(const unsigned int score);
    void setPlayerPassed(const bool passed);

    std::string getPlayerName() const;
    unsigned int getPlayerAge() const;
    unsigned int getPlayerScore() const;
    unsigned int getPlayerLandsCount() const;
    bool getPlayerPassed() const;

    std::vector<std::shared_ptr<Card>> getCard(bool hand = true) const;

    void addCard(const std::vector<std::shared_ptr<Card>> &cards, bool toHand = true);

    void addLand(std::shared_ptr<Land> land);

    void clearPlayedCard();

    std::shared_ptr<Card> selectCard(const std::string &p_card);

    void playCard(std::string cardName);
};

#endif // PLAYER_H