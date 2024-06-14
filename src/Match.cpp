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

void Match::setSeason(std::shared_ptr<Special> season)
{
    this->season = season;
}

std::shared_ptr<Special> Match::getSeason() const { return this->season; }

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

void Match::playerChoice(std::shared_ptr<Player> player)
{
    terminal_handler.print("Select a card to play : \n");
    for (std::shared_ptr<Card> card : player->getCard())
    {
        terminal_handler.print(card->getCardName() + " ");
    }
    terminal_handler.print("\n");
    std::string cardName;
    terminal_handler.input(cardName);
    if (cardName == "Scarecrow")
    {
        for (std::shared_ptr<Card> card : player->getCard())
        {
            if (card->getCardName() == cardName)
            {
                card->use(player, terminal_handler);
            }
        }
    }
    player->playCard(cardName);
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
    for (i; i < playersSize; i++)
    {
        if (players[i]->getPlayerPassed())
            continue;
        this->playerChoice(players[i]);
        this->calculateScore();
        if (i == playersSize - 1 && this->passCounter() != playersSize)
        {
            i = 0;
        }
    }
    this->stateWinner();
}

void Match::calculateScore()
{
    for (std::shared_ptr<Player> player : players)
    {
        for (std::shared_ptr<Card> card : player->getCard(false))
        {
            if (card->getCardType() == "Soldier")
            {
                card->use(player, terminal_handler);
            }
        }
        if (this->getSeason() != nullptr && this->getSeason()->getCardName() == "Winter")
        {
            std::shared_ptr<Winter> winter = std::dynamic_pointer_cast<Winter>(season);
            winter->use(players, terminal_handler);
        }
        for (std::shared_ptr<Card> card : player->getCard(false))
        {
            if (card->getCardName() == "Drummer")
            {
                card->use(player, terminal_handler);
                break;
            }
        }
        if (this->getSeason() != nullptr && this->getSeason()->getCardName() == "Spring")
        {
            std::shared_ptr<Spring> spring = std::dynamic_pointer_cast<Spring>(season);
            spring->use(players, terminal_handler);
        }
    }
}

void Match::stateWinner()
{
    this->calculateScore();
    std::shared_ptr<Player> winner;
    winner->setPlayerScore(0);
    for (std::shared_ptr<Player> player : players)
    {
        if (player->getPlayerScore() > winner->getPlayerScore())
        {
            winner->setPlayerScore(player->getPlayerScore());
        }
    }
    int maxCounter = 0;
    for (std::shared_ptr<Player> player : players)
    {
        if (player->getPlayerScore() == winner->getPlayerScore())
        {
            maxCounter++;
        }
    }
    if (maxCounter < 2)
    {
        winner->addLand(this->warSign->getLand());
        this->warSign->getLand()->setLandOwner(winner->getSign());
        this->warSign->setOwner(winner);
        if (winner->getPlayerLandsCount() == 5)
        {
            this->winner(winner);
        }
    }
    else
    {
        terminal_handler.print("Nobody wins!\n");
        this->war();
    }
}

void Match::winner(std::shared_ptr<Player> winner) {}