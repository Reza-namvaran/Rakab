#include "Sleipnir.hpp"

Sleipnir::Sleipnir(const std::string &p_name) : Special(p_name,"../assets/pics/sleipnir.png") {}

void Sleipnir::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {}

void Sleipnir::use(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> owner, std::shared_ptr<WarSign> warSign, unsigned int &passCounter)
{
  warSign->setOwner(owner);

  owner->setPlayerScore(INT_MAX);

  for (std::shared_ptr<Player> player : players)
  {
    if (!player->getPlayerPassed())
    {
      player->setPlayerPassed(true);
      passCounter++;
    }
  }
}