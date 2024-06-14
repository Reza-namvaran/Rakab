#include "Spring.hpp"

Spring::Spring(const std::string &p_name) : Special("Spring") {}

void Spring::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {}

void Spring::use(std::vector<std::shared_ptr<Player>> &players, IO_Interface &terminal_handler) {
    terminal_handler.print("Spring has been played!\n");

    int max = 0;
    for (const auto &player : players) {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        if (!playedCards.empty()) {
            for (const auto &card : playedCards) {
                if (card->getCardType() == "Soldier") {
                    auto soldier = std::dynamic_pointer_cast<Soldier>(card);
                    if (soldier) {
                        max = max > soldier->getCardScore() ? max :soldier->getCardScore();
                    }
                }
            }
        }
    }

    for (const auto &player : players) {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        for (const auto &card : playedCards) {
            if (card->getCardType() == "Soldier") {
                auto soldier = std::dynamic_pointer_cast<Soldier>(card);
                if (soldier && soldier->getCardScore() == max) {
                    player->setPlayerScore(player->getPlayerScore() + 3);
                }
            }
        }
    }
}