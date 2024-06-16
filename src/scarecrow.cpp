#include "Scarecrow.hpp"

Scarecrow::Scarecrow(const std::string p_name) : Special("Scarecrow") {}

void Scarecrow::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler)
{
    std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
    bool exists = false;
    if (!playedCards.empty())
    {
        terminal_handler.print("Choose one of these cards to back into your hand: \n");
        for (const auto &card : playedCards)
        {
            if (card->getCardType() == "Soldier")
            {
                exists = true;
                terminal_handler.print(card->getCardName(), false);
            }
        }
        terminal_handler.print("");
        if (!exists)
        {
            return;
        }
        int flag = 2;
        do
        {
            if (flag != 2)
                terminal_handler.print("Invalid choice! Please try again...");
            flag = 1;
            std::string cardName;
            terminal_handler.input(cardName);
            for (const auto &card : playedCards)
            {
                if (card->getCardType() == "Soldier" && card->getCardName() == cardName)
                {
                    std::vector<std::shared_ptr<Card>> handCards = player->getCard(true);
                    handCards.emplace_back(card);
                    player->addCard(handCards);
                    playedCards.erase(std::remove(playedCards.begin(), playedCards.end(), card), playedCards.end());
                    player->addCard(playedCards, false);
                    flag = 0;
                    break;
                }
            }
        } while (flag);
    }
}