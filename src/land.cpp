#include "Land.hpp"

Land::Land() {}

Land::Land(const std::string &p_name)
{
  this->name = p_name;
}

std::string Land::getLandName() const { return this->name; }
