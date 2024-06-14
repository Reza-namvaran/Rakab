#include "WarSign.hpp"

WarSign::WarSign() : Sign("black") {}

void WarSign::setLand(std::shared_ptr<Land> land)
{
    this->land = land;
}
std::shared_ptr<Land> WarSign::getLand() const { return this->land; }