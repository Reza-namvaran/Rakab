#include "Winter.hpp"

Winter::Winter(const std::string &p_name) : Special("Winter") {}

void Winter::use(Player &player, IO_Interface &terminal_handler) {}

void use(std::unordered_set<Player *> &players, IO_Interface &terminal_handler)
{
  terminal_handler.print("Winter has been played\n");
  for (Player *player : players)
  {
    std::unordered_set<Card *> playedCards = player->getCard(false);
    if (!playedCards.empty())
    {
      int score = 0;
      for (Card *card : playedCards)
      {
        if (card->getCardType() == "Soldier")
        {
          score++;
        }
      }
      player->setPlayerScore(score);
    }
  }
}