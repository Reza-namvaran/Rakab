#include "Sign.hpp"

Sign::Sign(const std::string& p_color){
  this->color = p_color;
}

std::vector<Land> Sign::getLands() const { return this->lands; }

void Sign::addLand(Land& p_land){
  this->lands.emplace_back(p_land);
}
