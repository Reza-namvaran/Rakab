#ifndef SCARECROW_H
#define SCARECROW_H

#include <algorithm>

#include "Special.hpp"

class Scarecrow : public Special
{
public:
  Scarecrow(const std::string p_name);

  virtual void use(Player &player, IO_Interface &terminal_handler) override;
};

#endif // SCARECROW_H
