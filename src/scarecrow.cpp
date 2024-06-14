#include "Scarecrow.hpp"

Scarecrow::Scarecrow(const std::string p_name) : Special("Scarecrow") {}

void Scarecrow::use(Player &player, IO_Interface &terminal_handler)
{
  std::vector<Card *> playedCards = player.getCard(false);
  if (!playedCards.empty())
  {
    terminal_handler.print("Choose one of these cards to back into your hand : \n");
    int counter = 0;
    for (const Card *card : playedCards)
    {
      if (card->getCardType() == "Soldier")
      {
        terminal_handler.print(std::to_string(++counter) + "." + card->getCardName() + " ");
      }
    }
    terminal_handler.print("\n");
    int flag = 2;
    do
    {
      if (flag != 2)
        terminal_handler.print("invalid choose! please try again...\n");
      flag = 1;
      std::string cardName;
      terminal_handler.input(cardName);
      int counter2 = 0;
      for (Card *card : playedCards)
      {
        if (card->getCardType() == "Soldier" && card->getCardName() == cardName)
        {
          counter2++;
          if (counter2 == counter)
          {
            std::vector<Card *> handCards = player.getCard(false);
            handCards.emplace_back(card);
            player.addCard(handCards);
            playedCards.erase(std::find(playedCards.begin(), playedCards.end(), card));
            flag = 0;
            break;
          }
        }
      }
    } while (flag);
  }
}
