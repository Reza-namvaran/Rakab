#ifndef SPY_H
#define SPY_H

#include "Special.hpp"

class Spy : public Special
{
  public:
    Spy(const std::string& p_name);

    virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) override;    
};

#endif