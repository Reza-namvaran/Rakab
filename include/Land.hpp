#ifndef LAND_H
#define LAND_H

#include <iostream>

class Land{
  private:
    std::string name;
    /// TODO: add Sign

  public:
    Land(const std::string& p_name);
    
    std::string getLandName() const;

   /// TODO: setLandOwner() method
};

#endif
