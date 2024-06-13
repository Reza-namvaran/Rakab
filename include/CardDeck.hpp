#ifndef CARD_DECK_H
#define CARD_DECK_H

#include <random>
#include <unordered_map>
#include <unordered_set>
#include "Player.hpp"
#include "Card.hpp"
#include "Special.hpp"
#include "Winter.hpp"
#include "Spring.hpp"
#include "Soldier.hpp"
#include "Heroine.hpp"
#include "Drummer.hpp"
#include "Scarecrow.hpp"

class CardDeck {
   private:
      std::unordered_multiset<Card*> deck;
      std::unordered_map<std::string, int> card_type_count;

   public:
    CardDeck();

    ~CardDeck();

    void shuffleCards();

    void generateDeck();

    std::unordered_multiset<Card*> getDeck() const;

    void setCardDeck(std::unordered_multiset<Card*> p_deck);

    void dealCard(Player* p_player);
};

#endif // CARD_DECK_H