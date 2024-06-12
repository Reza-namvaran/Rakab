#ifndef SPECIAL_H
#define SPECIAL_H

#include "Card.hpp"

class Special : public Card
{
public:
    Special(const std::string p_name);

    virtual void use(std::unordered_set<Card *> &hand_cards, std::unordered_set<Card *> &player_cards, Player &player, IO_Interface &terminal_handler) override = 0;

    std::string getCardType() const override;
};

#endif // SPECIAL_H
