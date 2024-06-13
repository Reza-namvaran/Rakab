#ifndef WARSGIN_H
#define WARSGIN_H

#include <iostream>
#include "Sign.hpp"
#include "Land.hpp"

class WarSign : public Sign
{
private:
    Land land;

public:
    WarSign();

    void setLand(const Land &land);
    Land getLand() const;
};

#endif