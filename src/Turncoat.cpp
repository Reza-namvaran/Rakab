#include "Turncoat.hpp"

Turncoat::Turncoat(const std::string& p_name) : Special(p_name) {}

void Turncoat::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler)
{
  player->setPlayerPassed(true);
}
