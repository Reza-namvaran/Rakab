#ifndef PEACESIGN_H
#define PEACESIGN_H

#include <iostream>
#include "Sign.hpp"
#include "Land.hpp"

class PeaceSign : public Sign
{
   private:
    std::shared_ptr<Land> land;

   public:
    PeaceSign();

    void setLand(std::shared_ptr<Land> land);
    
    std::shared_ptr<Land> getLand() const;
};

#endif // PEACESIGN_H