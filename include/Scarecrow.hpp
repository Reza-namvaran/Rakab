#ifndef SCARECROW_H
#define SCARECROW_H

#include "Card.hpp"

class Scarecrow : public Card{
  public:
    Scarecrow(const std::string p_name, const std::string p_description);

    virtual void use(std::unordered_set<Card*> player_cards) override;
};

#endif // SCARECROW_H
