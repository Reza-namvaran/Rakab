#ifndef SIGN_H
#define SIGN_H

#include <iostream>
#include <vector>
#include <memory>

#include "Player.hpp"

class Player;

class Sign {
private:
    std::string color;
    std::shared_ptr<Player> owner;

public:
    Sign();
    Sign(const std::string &p_color);

    void setOwner(std::shared_ptr<Player> owner);
    std::shared_ptr<Player> getOwner() const;
};

#endif // SIGN_H