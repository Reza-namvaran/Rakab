#include "CardDeck.hpp"

CardDeck::CardDeck() {
    this->generateDeck();
}

CardDeck::~CardDeck() {
    // Clean up memory
    for (Card* card : deck) {
        delete card;
    }
}

void CardDeck::generateDeck() {
    card_type_count = {
        {"One", 8},
        {"Two", 8},
        {"Three", 8},
        {"Four", 8},
        {"Five", 8},
        {"Six", 8},
        {"Ten", 10},
        {"Heroine", 3},
        {"Winter", 3},
        {"Spring", 3},
        {"Drummer", 6},
        {"Scarecrow", 16},
    };

    for (const auto& pair : card_type_count) {

        for (int i = 0; i < pair.second; ++i) {

            if (pair.first == "Heroine")
                deck.emplace(new Heroine("Heroine"));

            else if (pair.first == "Winter")
                deck.emplace(new Winter("Winter"));

            else if (pair.first == "Spring")
                deck.emplace(new Spring("Spring"));

            else if (pair.first == "Drummer")
                deck.emplace(new Drummer("Drummer"));

            else if (pair.first == "Scarecrow")
                deck.emplace(new Scarecrow("Scarecrow"));
            
            else
                deck.emplace(new Soldier(pair.first, pair.second));

        }

    }
}

std::unordered_multiset<Card*> CardDeck::getDeck() const {
    return this->deck;
}

void CardDeck::shuffleCards() {}

void CardDeck::setCardDeck(std::unordered_multiset<Card*> p_deck) {
    // Clear existing deck
    for (Card* card : deck) {
        delete card;
    }
    this->deck = p_deck;  // Assuming ownership is transferred
}

void CardDeck::dealCard(Player* p_player) {}