#include "Sign.hpp"

Sign::Sign(const std::string &p_color) : color(p_color), owner(nullptr) {}

void Sign::setOwner(std::shared_ptr<Player> p_owner) {
    owner = p_owner;
}

std::shared_ptr<Player> Sign::getOwner() const {
    return owner;
}

void Sign::setColor(const std::string& p_color) {
    this->color = p_color;
}

std::string Sign::getColor() const { return this->color; }