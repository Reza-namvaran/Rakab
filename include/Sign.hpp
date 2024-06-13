#ifndef SIGN_H
#define SIGN_H

#include <iostream>
#include <vector>

#include "Player.hpp"

class Player;

class Sign{
  private:
    std::string color;
    Player* owner;

  public:
    Sign();
    Sign(const std::string& p_color);
};

#endif // SIGN_H
