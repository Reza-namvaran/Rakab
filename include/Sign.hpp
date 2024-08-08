#ifndef SIGN_H
#define SIGN_H

#include <iostream>
#include <vector>
#include <memory>

#include "raylib.h"
#include "Player.hpp"

class Player;

class Sign {
private:
    std::string color;
    std::shared_ptr<Player> owner;
    Texture2D icon;

public:
    Sign(const std::string &p_color);

    ~Sign();

    void setOwner(std::shared_ptr<Player> owner);
    std::shared_ptr<Player> getOwner() const;

    void setColor(const std::string& p_color);

    Texture2D getIcon();

    std::string getColor() const;
};

#endif // SIGN_H