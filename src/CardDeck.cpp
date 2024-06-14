#include "CardDeck.hpp"

CardDeck::CardDeck()
{
    this->generateDeck();
}

CardDeck::~CardDeck()
{
    // Clean up memory
    for (Card *card : deck)
    {
        delete card;
    }
}

void CardDeck::generateDeck()
{
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

    for (const auto &pair : card_type_count)
    {

        for (int i = 0; i < pair.second; ++i)
        {

            if (pair.first == "Heroine")
                deck.emplace_back(new Heroine("Heroine"));

            else if (pair.first == "Winter")
                deck.emplace_back(new Winter("Winter"));

            else if (pair.first == "Spring")
                deck.emplace_back(new Spring("Spring"));

            else if (pair.first == "Drummer")
                deck.emplace_back(new Drummer("Drummer"));

            else if (pair.first == "Scarecrow")
                deck.emplace_back(new Scarecrow("Scarecrow"));

            else
                deck.emplace_back(new Soldier(pair.first, pair.second));
        }
    }
}

std::vector<Card *> CardDeck::getDeck() const
{
    return this->deck;
}

void CardDeck::shuffleCards()
{
    std::random_shuffle(this->deck.begin(), this->deck.end());
}

void CardDeck::setCardDeck(std::vector<Card *> p_deck)
{
    // Clear existing deck
    for (Card *card : deck)
    {
        delete card;
    }
    this->deck = p_deck; // Assuming ownership is transferred
}

void CardDeck::dealCard(Player *p_player)
{
    int count = 10 + p_player->getPlayerLandsCount();
    std::vector<Card *> cards;
    for (int i = 0; i < count; i++)
    {
        int random = rand() / this->deck.size();
        cards.push_back(this->deck[random]);
        this->deck.erase(this->deck.begin() + random);
    }
    p_player->addCard(cards);
}