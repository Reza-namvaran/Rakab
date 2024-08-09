#include "Special.hpp"

Special::Special(const std::string& p_name, const char *cardPicPath) : Card(p_name,cardPicPath){}

std::string Special::getCardType() const { return "Special"; }