#ifndef LAND_H
#define LAND_H

#include <iostream>

class Sign;

class Land{
  private:
    std::string name;
    Sign* owner;

  public:
    Land();
    Land(const std::string& p_name);
    
    std::string getLandName() const;

    void setLandOwner(Sign* p_owner);

    Sign* getLandOwner() const;
};

#endif
