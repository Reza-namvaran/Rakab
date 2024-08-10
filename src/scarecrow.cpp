#include "Scarecrow.hpp"

Scarecrow::Scarecrow(const std::string p_name) : Special("Scarecrow","../assets/pics/scarecrow.png") {}

void Scarecrow::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler)
{
    std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
    bool exists = false;
    std::vector<Rectangle> cards_positions;
    if (!playedCards.empty())
    {
        for (size_t idx = 0; idx < playedCards.size(); ++idx)
        {
            if (playedCards[idx]->getCardType() == "Soldier")
            {
                exists = true;
                cards_positions.emplace_back((Rectangle){(float)(80 + idx * 80), 350, 70, 108});
            }
        }
        if (!exists)
        {
            return;
        }

        std::vector<std::shared_ptr<Card>> handCards = player->getCard(true);
        bool flag = true;
        do
        {
            int it = 0;
            for (Rectangle card_pos : cards_positions)
            {
                if (playedCards[it]->getCardType() == "Soldier")
                {
                    if (CheckCollisionPointRec(GetMousePosition(), card_pos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        handCards.emplace_back(playedCards[it]);
                        player->addCard(handCards);
                        playedCards.erase(std::remove(playedCards.begin(), playedCards.end(), playedCards[it]), playedCards.end());
                        player->addCard(playedCards, false);
                        flag = false;
                        break;
                    }
                    it++;
                }
                else
                {
                    it++;
                }

            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            for (size_t idx = 0; idx < playedCards.size(); ++idx)
            {
                DrawTexture(playedCards[idx]->getCardPic(), 80 + idx * 80, 350, WHITE);
            }

            EndDrawing();
        } while (flag);
    }
}