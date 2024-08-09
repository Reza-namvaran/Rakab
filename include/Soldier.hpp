#ifndef SOLDIER_H
#define SOLDIER_H

#include "Card.hpp"
#include <cstdio>
#include <cstring>

class Soldier : public Card
{
private:
   unsigned int score;

public:
   Soldier(const std::string p_name, const unsigned int score);

   virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) override;

   std::string getCardType() const override;

   void setCardScore(const unsigned int &p_score);

   unsigned int getCardScore() const;
};

#endif // SOLDIER_H
