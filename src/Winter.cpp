#include "Winter.hpp"

Winter::Winter(const std::string &p_name) : Special("Winter") {}

void Winter::use(Player &player, IO_Interface &terminal_handler) {}

void Winter::use(std::vector<std::shared_ptr<Player>> &players, IO_Interface &terminal_handler) {
    terminal_handler.print("Winter has been played\n");
    for (const auto &player : players) {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        if (!playedCards.empty()) {
            int score = 0;
            for (const auto &card : playedCards) {
                if (card->getCardType() == "Soldier") {
                    score++;
                }
            }
            player->setPlayerScore(score);
        }
    }
}