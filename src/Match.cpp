#include "Match.hpp"

Match::Match(std::vector<std::shared_ptr<Player>> p_players) : players(p_players), deck(std::make_shared<CardDeck>()), warSign(std::make_shared<WarSign>())
{
    this->lands = {
        std::make_shared<Land>("ELINIA"),
        std::make_shared<Land>("ROLLO"),
        std::make_shared<Land>("TALMONE"),
        std::make_shared<Land>("PLADACI"),
        std::make_shared<Land>("MORINA"),
        std::make_shared<Land>("ARMENTO"),
        std::make_shared<Land>("LIA"),
        std::make_shared<Land>("OLIVADI"),
        std::make_shared<Land>("BORGE"),
        std::make_shared<Land>("DIMASE"),
        std::make_shared<Land>("BELLA"),
        std::make_shared<Land>("CALINE"),
        std::make_shared<Land>("ENNA"),
        std::make_shared<Land>("ATELA")};
    this->adjacentList = {
        {std::make_shared<Land>("ELINIA"), std::make_shared<Land>("ROLLO"), std::make_shared<Land>("TALMONE")},
        {std::make_shared<Land>("MORINA"), std::make_shared<Land>("ROLLO"), std::make_shared<Land>("TALMONE")},
        {std::make_shared<Land>("MORINA"), std::make_shared<Land>("ARMENTO"), std::make_shared<Land>("TALMONE")},
        {std::make_shared<Land>("MORINA"), std::make_shared<Land>("ARMENTO"), std::make_shared<Land>("OLIVADI")},
        {std::make_shared<Land>("ARMENTO"), std::make_shared<Land>("LIA"), std::make_shared<Land>("OLIVADI")},
        {std::make_shared<Land>("MORINA"), std::make_shared<Land>("BORGE"), std::make_shared<Land>("PLADACI")},
        {std::make_shared<Land>("BORGE"), std::make_shared<Land>("DIMASE"), std::make_shared<Land>("OLIVADI")},
        {std::make_shared<Land>("ATELA"), std::make_shared<Land>("ENNA"), std::make_shared<Land>("DIMASE")},
        {std::make_shared<Land>("ENNA"), std::make_shared<Land>("BORGE"), std::make_shared<Land>("CALINE")},
        {std::make_shared<Land>("CALINE"), std::make_shared<Land>("BORGE"), std::make_shared<Land>("BELLA")},
        {std::make_shared<Land>("PLADACI"), std::make_shared<Land>("BELLA"), std::make_shared<Land>("CALINE")},
        {std::make_shared<Land>("CALINE"), std::make_shared<Land>("ENNA"), std::make_shared<Land>("ATELA")},
        {std::make_shared<Land>("BELLA"), std::make_shared<Land>("PLADACI"), std::make_shared<Land>("BORGE")},
        {std::make_shared<Land>("ROLLO"), std::make_shared<Land>("PLADACI"), std::make_shared<Land>("MORINA")},
        {std::make_shared<Land>("MORINA"), std::make_shared<Land>("BORGE"), std::make_shared<Land>("OLIVADI")},
        {std::make_shared<Land>("CALINE"), std::make_shared<Land>("BORGE"), std::make_shared<Land>("PLADACI")},
        {std::make_shared<Land>("ENNA"), std::make_shared<Land>("BORGE"), std::make_shared<Land>("DIMASE")}};
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

void Match::displayStatus() {
    
    /* First field of status -> players' score + played cards */
    std::string separator(50, '-');

    this->terminal_handler.print(separator);
    this->terminal_handler.print("\n");


    for(std::shared_ptr<Player> player : this->players)
    {
        this->terminal_handler.print(player->getPlayerName() + " [Score: " + std::to_string(player->getPlayerScore()) + "]");
        
        std::string cards = "";
        for(std::shared_ptr<Card> card : player->getCard(false))
        {
            cards += card->getCardName() + " ";
        }

        this->terminal_handler.print(cards);

        this->terminal_handler.print("");
    }

    this->terminal_handler.print(separator);

    /* End of first field */

    /* Second field of status -> Lands of each Player */

    for(std::shared_ptr<Player> player : this->players)
    {
        this->terminal_handler.print(player->getPlayerName() + ":");

        std::string player_lands = "";
        
        if(!player->getSign()->getLands().empty())
        {
            for(std::shared_ptr<Land> land : player->getSign()->getLands())
            {
                player_lands += land->getLandName() + " ";
            }
;
            this->terminal_handler.print(player_lands);
        }
        else
        {
            this->terminal_handler.print("");
        }
    }

    /* End of second field */
}

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

void Match::refreshData()
{
    this->passCounter = 0;
    this->lastPlayerPassed = nullptr;
    for (std::shared_ptr<Player> player : players)
    {
        player->refreshData();
    }
}

unsigned int Match::findStarterPlayer() const
{
    int i = 0;
    for (i; i < players.size(); i++)
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
    terminal_handler.print(player->getPlayerName() + " Select a card to play : \n");
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
    else if (cardName == "pass")
    {
        player->setPlayerPassed(true);
        this->passCounter++;
        this->lastPlayerPassed = player;
    }
    player->playCard(cardName);
}

void Match::setWarLand()
{
    terminal_handler.print(this->warSign->getOwner()->getPlayerName() + ", You shall choose a land for war :\n");
    for (std::shared_ptr<Land> land : this->lands)
    {
        if (land->getLandOwner() == nullptr)
        {
            terminal_handler.print(land->getLandName() + " ");
        }
    }
    terminal_handler.print("\n");
    std::string landName;
    terminal_handler.input(landName);
    for (std::shared_ptr<Land> land : lands)
    {
        if (land->getLandName() == landName)
        {
            this->warSign->setLand(land);
            break;
        }
    }
}

void Match::run()
{
    while (!this->is_match_over)
    {
        this->terminal_handler.clearScreen();
        this->setWarLand();
        this->displayStatus();
        this->refreshData();
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
        if (i == playersSize - 1 && this->passCounter != playersSize)
        {
            i = -1;
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
        this->winner(winner);
        this->setWarLand();
    }
    else
    {
        terminal_handler.print("Nobody wins!\n");
        this->warSign->setOwner(this->lastPlayerPassed);
    }
}

void Match::winner(std::shared_ptr<Player> winner)
{
    if (winner->getPlayerLandsCount() == 5)
    {
        this->is_match_over = true;
    }
    int counter;
    for (std::vector<std::shared_ptr<Land>> list : this->adjacentList)
    {
        if (list[0]->getLandOwner()->getPlayerName() == list[1]->getLandOwner()->getPlayerName() && list[0]->getLandOwner()->getPlayerName() == list[2]->getLandOwner()->getPlayerName())
        {
            this->is_match_over = true;
        }
    }
}
