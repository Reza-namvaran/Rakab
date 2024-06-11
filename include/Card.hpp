#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <unordered_set>

class Card{
  protected:
    std::string name;
    std::string description;

  public:
    Card(const std::string p_name, const std::string p_description);

    virtual ~Card() = default;
    
    virtual void use(std::unordered_set<Card*> cards) = 0;

    std::string getCardName() const;

    std::string getCardDescription() const;
};

#endif
