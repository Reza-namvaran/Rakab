#include "Bishop.hpp"

Bishop::Bishop(const std::string &p_name) : Special("Bishop") {}

void Bishop::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {}

void Bishop::use(std::vector<std::shared_ptr<Player>> &players)
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
        if (playedCards.empty())
            continue;
        std::vector<std::shared_ptr<Card>> newPlayedCards = playedCards;
        int iterator = 0;
        for (std::shared_ptr<Card> card : playedCards)
        {
            if (card->getCardType() == "Soldier")
            {
                std::shared_ptr<Soldier> soldier = std::dynamic_pointer_cast<Soldier>(card);
                if (soldier->getCardScore() == max)
                {
                    newPlayedCards.erase(newPlayedCards.begin() + iterator - (playedCards.size() - newPlayedCards.size()));
                }
            }
            iterator++;
        }
        player->addCard(newPlayedCards, false);
    }
}