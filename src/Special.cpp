#include "Special.hpp"

Special::Special(const std::string p_name) : Card(p_name){}

std::string Special::getCardType() const { return "Special"; }