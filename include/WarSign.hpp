#ifndef WARSGIN_H
#define WARSGIN_H

#include <iostream>
#include "Sign.hpp"
#include "Land.hpp"

class WarSign : public Sign
{
private:
    std::shared_ptr<Land> land;

public:
    WarSign();

    void setLand(std::shared_ptr<Land> land);
    
    std::shared_ptr<Land> getLand() const;
};

#endif