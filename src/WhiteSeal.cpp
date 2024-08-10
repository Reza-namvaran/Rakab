#include "WhiteSeal.hpp"

WhiteSeal::WhiteSeal(const std::string p_name) : Special(p_name, "../assets/pics/whiteseal.png") {}

void WhiteSeal::use(std::shared_ptr<Player> p_player, IO_Interface& terminal_handler) {}

void WhiteSeal::use(std::vector<std::shared_ptr<Player>> players)
{
  for (auto player : players)
  {
    std::vector<std::shared_ptr<Card>> played_cards = player->getCard(false);

    /// DESCRIPTION: Removing all cards that player has played
    for(auto card : played_cards)
    {
      played_cards.erase(std::remove(played_cards.begin(), played_cards.end(), card), played_cards.end());
    }

    player->addCard(played_cards, false);
  }
  
  std::clog << "WhiteSeal played" << std::endl;
}
