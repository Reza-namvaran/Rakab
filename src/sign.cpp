#include "Sign.hpp"

Sign::Sign() : color(""), owner(nullptr) {}

Sign::Sign(const std::string &p_color) : color(p_color), owner(nullptr) {}

void Sign::setOwner(std::shared_ptr<Player> p_owner) {
    owner = p_owner;
}

std::shared_ptr<Player> Sign::getOwner() const {
    return owner;
}