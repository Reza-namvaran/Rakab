#ifndef LAND_H
#define LAND_H

#include <iostream>
#include <memory>
#include <string>

#include "raylib.h"

class PlayerSign;
class Player;

class Land
{
private:
    std::string name;
    std::shared_ptr<PlayerSign> owner;
    Rectangle border;

public:
    Land();
    Land(const std::string &p_name, Rectangle p_border);

    void setLandOwner(std::shared_ptr<PlayerSign> p_owner);

    std::shared_ptr<Player> getLandOwner() const;

    std::string getLandName() const;

    Rectangle getBorder();
};

#endif