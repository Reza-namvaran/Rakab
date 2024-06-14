#ifndef LAND_H
#define LAND_H

#include <iostream>
#include <memory>
#include <string>

class Sign;

class Land {
private:
    std::string name;
    std::shared_ptr<Sign> owner;

public:
    Land();
    Land(const std::string& p_name);

    std::string getLandName() const;

    void setLandOwner(std::shared_ptr<Sign> p_owner);

    std::shared_ptr<Sign> getLandOwner() const;
};

#endif