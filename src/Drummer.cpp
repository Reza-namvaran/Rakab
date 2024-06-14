#include "Drummer.hpp"

Drummer::Drummer(const std::string p_name) : Special("Drummer") {}

void Drummer::use(Player &player, IO_Interface &terminal_handler)
{
  std::vector<Card *> playedCards = player.getCard(false);
  if (!playedCards.empty())
  {
    terminal_handler.print("Drummer has been played!"); 
    terminal_handler.print("All of " + player.getPlayerName() + "'s soldiers' score will be doubled. \n");

    for (Card *card : playedCards)
    {
      if (card->getCardType() == "Soldier")
      {
        Soldier *soldier = dynamic_cast<Soldier *>(card);
        soldier->setCardScore(soldier->getCardScore() * 2);
      }
    }
  }
}
