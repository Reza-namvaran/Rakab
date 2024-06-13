#ifndef PLAYERSIGN_H
#define PLAYERSIGN_H

#include <iostream>
#include "Sign.hpp"
#include "Land.hpp"

class PlayerSign : public Sign
{
private:
  std::vector<Land> lands;

public:
  PlayerSign(const std::string &p_color);

  void setLand(const Land &land);
  std::vector<Land> getLands() const;
};

#endif