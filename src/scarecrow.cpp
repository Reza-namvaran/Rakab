#include "Scarecrow.hpp"

Scarecrow::Scarecrow(const std::string p_name) : Special(p_name) {}

void Scarecrow::use(std::unordered_set<Card *> &hand_cards, std::unordered_set<Card *> &player_cards, Player &player, IO_Interface &terminal_handler)
{
  if (!hand_cards.empty())
  {
    terminal_handler.print("Choose one of these cards to back into your hand : \n");
    int counter = 0;
    for (const Card *card : hand_cards)
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
      for (Card *card : hand_cards)
      {
        if (card->getCardType() == "Soldier" && card->getCardName() == cardName)
        {
          counter2++;
          if (counter2 == counter)
          {
            player_cards.insert(card);
            hand_cards.erase(card);
            flag = 0;
            break;
          }
        }
      }
    } while (flag);
  }
}
