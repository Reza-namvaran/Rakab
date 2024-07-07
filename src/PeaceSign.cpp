#include "PeaceSign.hpp"

PeaceSign::PeaceSign() : Sign("White") {}

void PeaceSign::setLand(std::shared_ptr<Land> land)
{
    this->land = land;
}

std::shared_ptr<Land> PeaceSign::getLand() const { return this->land; }