#include "CardDeck.hpp"

CardDeck::CardDeck() {}

CardDeck::~CardDeck() {}

void CardDeck::generateDeck()
{
    this->deck.clear();
    card_type_count = {
        {"One", std::make_pair(8, 1)},
        {"Two", std::make_pair(8, 2)},
        {"Three", std::make_pair(8, 3)},
        {"Four", std::make_pair(8, 4)},
        {"Five", std::make_pair(8, 5)},
        {"Six", std::make_pair(8, 6)},
        {"Ten", std::make_pair(10, 10)},
        {"Heroine", std::make_pair(3, 0)},
        {"Winter", std::make_pair(3, 0)},
        {"Spring", std::make_pair(3, 0)},
        {"Drummer", std::make_pair(6, 0)},
        {"Scarecrow", std::make_pair(16, 0)},
        {"Spy", std::make_pair(12, 0)},
        {"Turncoat", std::make_pair(3, 0)},
        {"Bishop", std::make_pair(6, 0)},
        {"Mirage", std::make_pair(6, 0)},
        {"WhiteSeal", std::make_pair(3, 0)},
        {"Sleipnir", std::make_pair(2, 0)},
    };

    for (const auto &pair : card_type_count)
    {
        for (int i = 0; i < pair.second.first; ++i)
        {
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
            else if (pair.first == "Spy")
                deck.emplace_back(std::make_shared<Spy>("Spy"));
            else if (pair.first == "Turncoat")
                deck.emplace_back(std::make_shared<Turncoat>("Turncoat"));
            else if (pair.first == "Bishop")
                deck.emplace_back(std::make_shared<Bishop>("Bishop"));
            else if (pair.first == "Mirage")
                deck.emplace_back(std::make_shared<Mirage>("Mirage"));
            else if (pair.first == "WhiteSeal")
                deck.emplace_back(std::make_shared<WhiteSeal>("WhiteSeal"));
            else if (pair.first == "Sleipnir")
                deck.emplace_back(std::make_shared<Sleipnir>("Sleipnir"));
            else
                deck.emplace_back(std::make_shared<Soldier>(pair.first, pair.second.second));
        }
    }
}

std::vector<std::shared_ptr<Card>> CardDeck::getDeck() const
{
    return this->deck;
}

void CardDeck::shuffleCards()
{
    std::shuffle(this->deck.begin(), this->deck.end(), std::mt19937{std::random_device{}()});
}

void CardDeck::setCardDeck(std::vector<std::shared_ptr<Card>> p_deck)
{
    this->deck = std::move(p_deck); // Assuming ownership is transferred
}

void CardDeck::dealCard(std::shared_ptr<Player> p_player)
{
    int count = 10 + p_player->getPlayerLandsCount();
    std::vector<std::shared_ptr<Card>> cards;
    for (int i = 0; i < count; i++)
    {
        size_t random_idx = rand() % this->deck.size();
        cards.push_back(this->deck[random_idx]);
        this->deck.erase(this->deck.begin() + random_idx);
    }
    p_player->addCard(cards);
}