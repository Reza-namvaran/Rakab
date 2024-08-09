#include "Spring.hpp"

Spring::Spring(const std::string &p_name) : Special("Spring","../assets/pics/spring.png") {}

void Spring::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {}

void Spring::use(std::vector<std::shared_ptr<Player>> &players, IO_Interface &terminal_handler)
{
    unsigned int max = 0;
    for (std::shared_ptr<Player> player : players)
    {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        if (!playedCards.empty())
        {
            for (std::shared_ptr<Card> card : playedCards)
            {
                if (card->getCardType() == "Soldier")
                {
                    std::shared_ptr<Soldier> soldier = std::dynamic_pointer_cast<Soldier>(card);
                    max = max > soldier->getCardScore() ? max : soldier->getCardScore();
                }
            }
        }
    }

    for (std::shared_ptr<Player> player : players)
    {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        for (std::shared_ptr<Card> card : playedCards)
        {
            if (card->getCardType() == "Soldier")
            {
                std::shared_ptr<Soldier> soldier = std::dynamic_pointer_cast<Soldier>(card);
                if (soldier->getCardScore() == max)
                {
                    player->setPlayerScore(player->getPlayerScore() + 3);
                }
            }
        }
    }
}