#ifndef DRUMMER_H
#define DRUMMER_H

#include "Special.hpp"

class Drummer : public Special {
  public:
    Drummer(const std::string p_name);

    virtual void use(std::unordered_set<Card*> cards) override;
};

#endif // DRUMMER_H
