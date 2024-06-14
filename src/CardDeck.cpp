#include "CardDeck.hpp"

CardDeck::CardDeck(){}

CardDeck::~CardDeck() {}

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

    for (const auto &pair : card_type_count) {
        for (int i = 0; i < pair.second; ++i) {
            if (pair.first == "Heroine")
                deck.emplace_back(std::make_shared<Heroine>("Heroine"));
            else if (pair.first == "Winter")
                deck.emplace_back(std::make_shared<Winter>("Winter"));
            else if (pair.first == "Spring")
                deck.emplace_back(std::make_shared<Spring>("Spring"));
            else if (pair.first == "Drummer")
                deck.emplace_back(std::make_shared<Drummer>("Drummer"));
            else if (pair.first == "Scarecrow")
                deck.emplace_back(std::make_shared<Scarecrow>("Scarecrow"));
            else
                deck.emplace_back(std::make_shared<Soldier>(pair.first, pair.second));
        }
    }
}

std::vector<std::shared_ptr<Card>> CardDeck::getDeck() const {
    return this->deck;
}

void CardDeck::shuffleCards() {
    std::random_shuffle(this->deck.begin(), this->deck.end());
}

void CardDeck::setCardDeck(std::vector<std::shared_ptr<Card>> p_deck) {
    this->deck = std::move(p_deck); // Assuming ownership is transferred
}

void CardDeck::dealCard(std::shared_ptr<Player> p_player) {
    int count = 10;
    std::vector<std::shared_ptr<Card>> cards;
    for (int i = 0; i < count; i++) {
        size_t random_idx = rand() % this->deck.size();
        cards.push_back(this->deck[random_idx]);
        this->deck.erase(this->deck.begin() + random_idx);
    }
    p_player->addCard(cards);
}