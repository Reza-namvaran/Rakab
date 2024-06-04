#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card{
  private:
    std::string name;
    std::string description;
    unsigned int score;

  public:
    Card();
    
    virtual void use() const;

    std::string getCardName() const;

    std::string getCardDescription() const;

    unsigned int getScore() const;
};

#endif
