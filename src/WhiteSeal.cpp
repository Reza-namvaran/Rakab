#include "WhiteSeal.hpp"

WhiteSeal::WhiteSeal(const std::string p_name) : Special(p_name, "../assets/pics/whiteseal.png") {}

void WhiteSeal::use(std::shared_ptr<Player> p_player, IO_Interface &terminal_handler) {}

void WhiteSeal::use(std::vector<std::shared_ptr<Player>> players)
{
  for (auto player : players)
  {
    std::vector<std::shared_ptr<Card>> temp;
    player->addCard(temp, false);

    /// DESCRIPTION: Removing all cards that player has played
  }

  std::clog << "WhiteSeal played" << std::endl;
}
