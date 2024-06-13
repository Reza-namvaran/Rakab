#include "Land.hpp"
#include "Sign.hpp"

Land::Land() {}

Land::Land(const std::string &p_name)
{
  this->name = p_name;
}

std::string Land::getLandName() const { return this->name; }


void Land::setLandOwner(Sign* p_owner){
  this->owner = p_owner;
}

Sign* Land::getLandOwner() const{ return this->owner; }