#include "Turncoat.hpp"

Turncoat::Turncoat(const std::string &p_name) : Special(p_name, "../assets/pics/turncoat.png") {}

void Turncoat::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {}

void Turncoat::use(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> lastPlayerPassed, std::shared_ptr<WarSign> warSign, unsigned int &passCounter)
{
  if (passCounter != 0)
  {
    warSign->setOwner(lastPlayerPassed);
  }
  else
  {
    bool flag = false;
    for (std::shared_ptr<Player> player : players)
    {
      for (std::shared_ptr<Card> card : player->getCard(false))
      {
        if (card->getCardName() == "Turncoat")
        {
          lastPlayerPassed = player;
          flag = true;
          break;
        }
        if (flag)
          break;
      }
    }
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