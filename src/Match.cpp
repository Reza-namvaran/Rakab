#include "Match.hpp"

Match::Match(std::vector<std::shared_ptr<Player>> p_players) : players(p_players), deck(std::make_shared<CardDeck>()), warSign(std::make_shared<WarSign>()) {
    unsigned int min_age = players[0]->getPlayerAge();
    int first_player = 0;
    for (int idx = 0; idx < players.size(); ++idx) {
        if (players[idx]->getPlayerAge() < min_age) {
            min_age = players[idx]->getPlayerAge();
            first_player = idx;
        }
    }
    warSign->setOwner(players[first_player]);
}

Match::~Match() {}

void Match::dealCard() {
    for (auto &player : players) {
        deck->dealCard(player);
    }
}

void Match::rechargeDeck()
{
    int playersCount = this->players.size();
    for (std::shared_ptr<Player> player : this->players)
    {
        if (player->getCard().size() == 0)
        {
            playersCount--;
        }
    }
    
    if (playersCount <= 1)
    {
        this->deck->generateDeck();
        this->deck->shuffleCards();
        this->dealCard();
    }
}

void Match::run() {
    std::cout << "Before Shuffle: \n" << std::endl;
    for (const auto &card : deck->getDeck()) {
        std::cout << card->getCardType() << " " << card->getCardName() << "\n";
    }

    deck->shuffleCards();

    std::cout << "After Shuffle: \n" << std::endl;
    for (const auto &card : deck->getDeck()) {
        std::cout << card->getCardType() << " " << card->getCardName() << "\n";
    }

    rechargeDeck();
   
    std::cout << players[0]->getCard(true).size() << "\n";
    for (const auto &card : players[0]->getCard(true)) {
        std::cout << card->getCardName() << " " << card->getCardType() << "\n";
    }
}