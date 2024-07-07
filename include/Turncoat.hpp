#ifndef TURNCOAT_H
#define TURNCOAT_H

#include "Special.hpp"
#include "Player.hpp"
#include "WarSign.hpp"

class Turncoat : public Special {
  public:
    Turncoat(const std::string& p_name);

    virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) override;

   void use(std::vector<std::shared_ptr<Player>> players,  std::shared_ptr<Player> lastPlayerPassed , std::shared_ptr<WarSign> warSign,unsigned int &passCounter);
};

#endif // TURNCOAT_H
