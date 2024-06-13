#include "Spring.hpp"

Spring::Spring(const std::string &p_name) : Special("Spring") {}

void Spring::use(Player &player, IO_Interface &terminal_handler) {}

void use(std::unordered_set<Player *> &players, IO_Interface &terminal_handler)
{
    terminal_handler.print("Spring has been played! \n");
    int max = 0;
    for (Player *player : players)
    {
        std::unordered_set<Card *> playedCards = player->getCard(false);
        if (!playedCards.empty())
        {
            for (Card *card : playedCards)
            {
                if (card->getCardType() == "Soldier")
                {
                    Soldier *soldier = dynamic_cast<Soldier *>(card);
                    max = max < soldier->getCardScore() ? soldier->getCardScore() : max;
                }
            }
        }
    }
    for (Player *player : players)
    {
        std::unordered_set<Card *> playedCards = player->getCard(false);
        for (Card *card : playedCards)
        {
            if (card->getCardType() == "Soldier")
            {
                Soldier *soldier = dynamic_cast<Soldier *>(card);
                if (soldier->getCardScore() == max)
                {
                    player->setPlayerScore(player->getPlayerScore() + 3);
                }
            }
        }
    }
}