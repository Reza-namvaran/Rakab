#include "Winter.hpp"

Winter::Winter(const std::string &p_name) : Special(p_name) {}

void Winter::use(Player &player, IO_Interface &terminal_handler)
{
  std::unordered_set<Card *> playedCards = player.getCard(false);
  if (!playedCards.empty())
  {
    terminal_handler.print("Winter has been played\n");
    int score = 0;
    for (Card *card : playedCards)
    {
      if (card->getCardType() == "Soldier")
      {
        score++;
      }
    }
    player.setPlayerScore(score);
  }
}