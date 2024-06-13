#include "WarSign.hpp"

WarSign::WarSign() : Sign("black") {}

void WarSign::setLand(const Land &land)
{
    this->land = land;
}
Land WarSign::getLand() const { return this->land; }
