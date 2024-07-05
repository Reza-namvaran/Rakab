#ifndef CARD_DECK_H
#define CARD_DECK_H

#include <random>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <memory>
#include <utility>

#include "Player.hpp"
#include "Card.hpp"
#include "Special.hpp"
#include "Winter.hpp"
#include "Spring.hpp"
#include "Soldier.hpp"
#include "Heroine.hpp"
#include "Drummer.hpp"
#include "Scarecrow.hpp"
#include "Spy.hpp"

class CardDeck
{
private:
    std::vector<std::shared_ptr<Card>> deck;
    std::unordered_map<std::string, std::pair<int, int>> card_type_count;

public:
    CardDeck();

    ~CardDeck();

    void shuffleCards();
    void generateDeck();

    std::vector<std::shared_ptr<Card>> getDeck() const;
    void setCardDeck(std::vector<std::shared_ptr<Card>> p_deck);
    void dealCard(std::shared_ptr<Player> p_player);
};

#endif // CARD_DECK_H