#include "PlayerSign.hpp"

PlayerSign::PlayerSign() {}

PlayerSign::PlayerSign(const std::string &p_color) : Sign(p_color) {}

void PlayerSign::setLand(std::shared_ptr<Land> land)
{
    this->lands.push_back(land);
}

std::vector<std::shared_ptr<Land>> PlayerSign::getLands() const { return this->lands; }