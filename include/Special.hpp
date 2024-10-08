#ifndef SPECIAL_H
#define SPECIAL_H


#include "Card.hpp"

class Special : public Card
{
public:
    Special(const std::string& p_name, const char *cardPicPath);

    virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) override = 0;

    std::string getCardType() const override;
};

#endif // SPECIAL_H
