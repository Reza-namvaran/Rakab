#include "Scarecrow.hpp"


Scarecrow::Scarecrow(const std::string p_name) : Special("Scarecrow") {}

void Scarecrow::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {
    std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
    if (!playedCards.empty()) {
        terminal_handler.print("Choose one of these cards to back into your hand: \n");
        int counter = 0;
        for (const auto &card : playedCards) {
            if (card->getCardType() == "Soldier") {
                terminal_handler.print(std::to_string(++counter) + "." + card->getCardName() + " ");
            }
        }
        terminal_handler.print("\n");
        int flag = 2;
        do {
            if (flag != 2)
                terminal_handler.print("Invalid choice! Please try again...\n");
            flag = 1;
            std::string cardName;
            terminal_handler.input(cardName);
            int counter2 = 0;
            for (const auto &card : playedCards) {
                if (card->getCardType() == "Soldier" && card->getCardName() == cardName) {
                    ++counter2;
                    if (counter2 == counter) {
                        std::vector<std::shared_ptr<Card>> handCards = player->getCard(true);
                        handCards.emplace_back(card);
                        player->addCard(handCards, true);
                        playedCards.erase(std::remove(playedCards.begin(), playedCards.end(), card), playedCards.end());
                        flag = 0;
                        break;
                    }
                }
            }
        } while (flag);
    }
}