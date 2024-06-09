#ifndef LAND_H
#define LAND_H

#include <iostream>

#include "Sign.hpp"

class Land{
  private:
    std::string name;
    Sign owner;

  public:
    Land(const std::string& p_name);
    
    std::string getLandName() const;

   /// TODO: setLandOwner() method
};

#endif
