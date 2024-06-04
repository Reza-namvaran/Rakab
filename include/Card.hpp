#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card{
  private:
    std::string name;
    std::string description;
    unsigned int score;

  public:
    virtual void use() = 0;

    std::string getCardName() const;

    std::string getCardDescription() const;

    unsigned int getScore() const;

    void setScore(const unsigned int& p_score);
};

#endif
