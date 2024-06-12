#ifndef SOLDIER_H
#define SOLDIER_H

#include "Card.hpp"

class Soldier : public Card
{
private:
   unsigned int score;

public:
   Soldier(const std::string p_name, const unsigned int score);

   virtual void use(std::unordered_set<Card *> cards);

   std::string getCardType() const override;

   void setCardScore(const unsigned int &p_score);

   unsigned int getCardScore() const;
};

#endif // SOLDIER_H
