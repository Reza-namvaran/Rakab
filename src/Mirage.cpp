#include "Mirage.hpp"

Mirage::Mirage(const std::string& p_name) : Special(p_name, "./assets/pics/mirage.png") {}

void Mirage::use(std::shared_ptr<Player> p_player, IO_Interface& terminal_handler) {
  std::vector<std::shared_ptr<Card>> played_cards = p_player->getCard(false);

  if (played_cards.empty())
  {
    played_cards.emplace_back(std::make_shared<Soldier>("Zero", 0));
    p_player->playCard("Mirage");
  }
  else
  {
    // Selecting a random card
    int random_card = std::rand() % played_cards.size();
    // Duplicating the card
    played_cards.emplace_back(played_cards[random_card]);

    // add duplicated card to played cards and remove mirage from player's hand
    p_player->addCard(played_cards, false);
    p_player->playCard("Mirage", false);
  }
}
