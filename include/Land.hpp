#ifndef LAND_H
#define LAND_H

#include <iostream>
#include <memory>
#include <string>

class PlayerSign;

class Land {
private:
    std::string name;
    std::shared_ptr<PlayerSign> owner;

public:
    Land();
    Land(const std::string& p_name);

    std::string getLandName() const;

    virtual void setLandOwner(std::shared_ptr<PlayerSign> p_owner);

    std::shared_ptr<PlayerSign> getLandOwner() const;
};

#endif