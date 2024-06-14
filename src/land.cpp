#include "Land.hpp"
#include "Sign.hpp"

Land::Land() : name(""), owner(nullptr) {}

Land::Land(const std::string& p_name) : name(p_name), owner(nullptr) {}

std::string Land::getLandName() const {
    return name;
}

void Land::setLandOwner(std::shared_ptr<Sign> p_owner) {
    owner = p_owner;
}

std::shared_ptr<Sign> Land::getLandOwner() const {
    return owner;
}