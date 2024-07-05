#ifndef TURNCOAT_H
#define TURNCOAT_H

#include "Special.hpp"

class Turncoat : public Special {
  public:
    Turncoat(const std::string& p_name);

    virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) override;
};

#endif // TURNCOAT_H
