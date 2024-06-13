#ifndef DRUMMER_H
#define DRUMMER_H

#include "Special.hpp"
#include "Soldier.hpp"

class Drummer : public Special
{
public:
  Drummer(const std::string p_name);

  virtual void use(Player &player, IO_Interface &terminal_handler) override;
};

#endif // DRUMMER_H
