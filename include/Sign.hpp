#ifndef SIGN_H
#define SIGN_H

#include <iostream>
#include <vector>

#include "Land.hpp"

class Sign{
  private:
    std::string color;
    std::vector<Land> lands;

  public:
    Sign(const std::string& p_color);
    
    std::vector<Land> getLands() const;

    void addLand(Land& p_land);
};

#endif
