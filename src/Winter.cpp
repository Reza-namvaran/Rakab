#include "Winter.hpp"

Winter::Winter(const std::string &p_name) : Special("Winter","../assets/pics/winter.png") {}

void Winter::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {}

void Winter::use(std::vector<std::shared_ptr<Player>> &players, IO_Interface &terminal_handler)
{
    for (const auto &player : players)
    {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        if (!playedCards.empty())
        {
            int score = 0;
            for (const auto &card : playedCards)
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