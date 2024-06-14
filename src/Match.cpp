#include "Match.hpp"

Match::Match(std::vector<std::shared_ptr<Player>> p_players) : players(p_players), deck(std::make_shared<CardDeck>()), warSign(std::make_shared<WarSign>())
{
    unsigned int min_age = players[0]->getPlayerAge();
    int first_player = 0;
    for (int idx = 0; idx < players.size(); ++idx)
    {
        if (players[idx]->getPlayerAge() < min_age)
        {
            min_age = players[idx]->getPlayerAge();
            first_player = idx;
        }
    }
    warSign->setOwner(players[first_player]);
}

Match::~Match() {}

void Match::dealCard()
{
    for (auto &player : players)
    {
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

unsigned int Match::passCounter() const
{
    int counter = 0;
    for (std::shared_ptr<Player> player : players)
    {
        if (player->getPlayerPassed())
        {
            counter++;
        }
    }
    return counter;
}

unsigned int Match::findStarterPlayer() const
{
    int i = 0;
    for (int i; i < players.size(); i++)
    {
        if (players[i]->getPlayerName() == warSign->getOwner()->getPlayerName())
        {
            break;
        }
    }
    return i;
}

void Match::run()
{
    while (!this->is_match_over)
    {
        this->rechargeDeck();
        this->war();
    }
}

void Match::war()
{
    int i = this->findStarterPlayer();
    int playersSize = players.size();
    for (int i; i < playersSize; i++)
    {
        if (players[i]->getPlayerPassed())
            continue;
        if (i == playersSize - 1 && this->passCounter() != playersSize)
        {
            i = 0;
        }
    }
}