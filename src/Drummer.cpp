#include "Drummer.hpp"

Drummer::Drummer(const std::string p_name) : Special("Drummer") {}

void Drummer::use(Player &player, IO_Interface &terminal_handler) {
    std::vector<std::shared_ptr<Card>> playedCards = player.getCard(false);
    if (!playedCards.empty()) {
        terminal_handler.print("Drummer has been played!");
        terminal_handler.print("All of " + player.getPlayerName() + "'s soldiers' scores will be doubled.\n");

        for (const auto &card : playedCards) {
            if (card->getCardType() == "Soldier") {
                auto soldier = std::dynamic_pointer_cast<Soldier>(card);
                if (soldier) {
                    soldier->setCardScore(soldier->getCardScore() * 2);
                }
            }
        }
    }
}