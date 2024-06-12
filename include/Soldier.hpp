#ifndef SOLDIER_H
#define SOLDIER_H

#include "Card.hpp"

class Soldier : public Card{
   private:
      unsigned int score;
      
      
   public:
      Soldier(const std::string p_name, const std::string p_desctiption);

      virtual void use(std::unordered_set<Card*> cards);

      void setCardScore(const unsigned int& p_score);

      unsigned int getCardScore() const;
};

#endif // SOLDIER_H
