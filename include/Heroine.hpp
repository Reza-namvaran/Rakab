#ifndef HEROINE_H
#define HEROINE_H

#include "Special.hpp"

class Heroine : public Special
{
public:
  Heroine(const std::string& p_name);

  virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) override;
};

#endif // HEROINE_H
