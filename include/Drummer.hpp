#ifndef DRUMMER_H
#define DRUMMER_H

#include "Card.hpp"
#include "Soldier.hpp"

class Drummer : public Card {
  public:
    Drummer(const std::string p_name, const std::string p_description);

    virtual void use(std::unordered_set<Card*> cards) override;
};

#endif // DRUMMER_H
