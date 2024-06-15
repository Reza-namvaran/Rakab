#ifndef PLAYERSIGN_H
#define PLAYERSIGN_H

#include <iostream>
#include "Sign.hpp"
#include "Land.hpp"

class PlayerSign : public Sign
{
private:
  std::vector<std::shared_ptr<Land>> lands;

public:
  PlayerSign(const std::string &p_color);

  void setLand(std::shared_ptr<Land> land);
    std::vector<std::shared_ptr<Land>> getLands() const;
};

#endif