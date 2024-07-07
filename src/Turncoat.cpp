#include "Turncoat.hpp"

Turncoat::Turncoat(const std::string &p_name) : Special(p_name) {}

void Turncoat::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {}

void Turncoat::use(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> lastPlayerPassed, std::shared_ptr<WarSign> warSign, unsigned int &passCounter)
{
  if (passCounter != 0)
  {
    warSign->setOwner(lastPlayerPassed);
  }

  for (std::shared_ptr<Player> player : players)
  {
    if (!player->getPlayerPassed())
    {
      player->setPlayerPassed(true);
      passCounter++;
    }
  }
}