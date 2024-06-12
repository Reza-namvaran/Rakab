#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <unordered_set>

#include "Card.hpp"
#include "Sign.hpp"

class Player
{
private:
    std::string name;
    unsigned int age;
    unsigned int total_score;
    std::unordered_set<Card *> hand;
    std::unordered_set<Card *> played;
    Sign sign;

public:
    Player(const std::string &p_name, const unsigned int &age);

    /// IMPORTANT: Decide on using full name or first & last name

    /// NOTE: Added setters, so players can change their personal info if needed.

    void setPlayerName(const std::string &p_name);

    void setPlayerAge(const unsigned int &p_age);

    void setPlayerScore(const unsigned int score);

    std::string getPlayerName() const;

    unsigned int getPlayerAge() const;

    unsigned int getPlayerScore() const;

    /// TODO: Do something for hand getter

    void addCard(const std::unordered_set<Card *> &cards, bool toHand = true);

    void clearPlayedCard();

    Card *selectCard(const std::string &p_card);
};

#endif
