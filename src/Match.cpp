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
        {this->lands[0], this->lands[1], this->lands[2]},
        {this->lands[4], this->lands[1], this->lands[2]},
        {this->lands[4], this->lands[5], this->lands[2]},
        {this->lands[4], this->lands[5], this->lands[7]},
        {this->lands[5], this->lands[6], this->lands[7]},
        {this->lands[4], this->lands[8], this->lands[3]},
        {this->lands[8], this->lands[9], this->lands[7]},
        {this->lands[13], this->lands[12], this->lands[9]},
        {this->lands[12], this->lands[8], this->lands[11]},
        {this->lands[11], this->lands[8], this->lands[10]},
        {this->lands[3], this->lands[10], this->lands[11]},
        {this->lands[11], this->lands[12], this->lands[13]},
        {this->lands[10], this->lands[3], this->lands[8]},
        {this->lands[1], this->lands[3], this->lands[4]},
        {this->lands[4], this->lands[8], this->lands[7]},
        {this->lands[11], this->lands[8], this->lands[3]},
        {this->lands[12], this->lands[8], this->lands[9]}};
        
    unsigned int min_age = players[0]->getPlayerAge();
    int first_player = 0;
    for (int idx = 0; idx < players.size(); ++idx)
    {
        if (players[idx]->getPlayerAge() <= min_age)
        {
            if (players[idx]->getPlayerAge() == min_age)
            {
                int random = rand() % 2;
                if (random)
                {
                    min_age = players[idx]->getPlayerAge();
                    first_player = idx;
                }
                continue;
            }
            min_age = players[idx]->getPlayerAge();
            first_player = idx;
        }
    }
    warSign->setOwner(players[first_player]);
}

Match::~Match() {}

void Match::displayStatus()
{

    /* First field of status -> players' score + played cards */
    std::string separator(50, '-');

    this->terminal_handler.print(separator);

    for (std::shared_ptr<Player> player : this->players)
    {
        if(!player->getPlayerPassed())
        {
            this->terminal_handler.print(player->getPlayerName() + " [Score: " + std::to_string(player->getPlayerScore()) + "]");
        }

        else
        {
            this->terminal_handler.print(player->getPlayerName() + " [Score: " + std::to_string(player->getPlayerScore()) + "]" + " Passed this turn");
        }
        
        std::string cards = "";
        for (std::shared_ptr<Card> card : player->getCard(false))
        {
            cards += card->getCardName() + " ";
        }

        this->terminal_handler.print(cards);

        this->terminal_handler.print("");
    }

    this->terminal_handler.print(separator);

    /* End of first field */

    /* Second field of status -> Lands of each Player */

    for (std::shared_ptr<Player> player : this->players)
    {
        this->terminal_handler.print(player->getPlayerName() + ":");

        std::string player_lands = "";

        if (!player->getSign()->getLands().empty())
        {
            for (std::shared_ptr<Land> land : player->getSign()->getLands())
            {
                player_lands += land->getLandName() + " ";
            };
            this->terminal_handler.print(player_lands);
        }
    }

    this->terminal_handler.print(separator);
    /* End of second field */

    /* Third field */

    this->terminal_handler.print("The Battle is in " + this->warSign->getLand()->getLandName());

    if (this->season)
        this->terminal_handler.print("Season: " + this->season->getCardName());
    else
        this->terminal_handler.print("Season: ---");

    /* End of third field*/
}

void Match::setSeason(std::shared_ptr<Special> season)
{
    this->season = season;
}

std::shared_ptr<Special> Match::getSeason() const { return this->season; }

void Match::dealCardsToPlayers()
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
        this->dealCardsToPlayers();
    }
}

void Match::refreshData()
{
    this->passCounter = 0;
    this->lastPlayerPassed = nullptr;
    this->season = nullptr;
    for (std::shared_ptr<Player> player : players)
    {
        player->resetPlayerData();
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

    std::unordered_set<std::string> player_cards;

    /// IMPORTANT: Avoid code duplication in here
    this->terminal_handler.print(player->getPlayerName() + "'s hand: \n");
    for (std::shared_ptr<Card> card : player->getCard())
    {
        player_cards.emplace(card->getCardName());
    }

    for(const auto& card : player_cards)
    {
        terminal_handler.print(card, false);
    }

    this->terminal_handler.print("\nSelect a card to play: ");
    std::string cardName;

    while(true){
        this->terminal_handler.input(cardName); 

        if(player_cards.find(cardName) != player_cards.end() || cardName == "pass")
        {
            break;
        }
        else if(cardName.find("help") != std::string::npos)
        {
            if(cardName == "help")
            {
                /// TODO:
            }
            else
            {
                std::string token = cardName.substr(cardName.find(" ") + 1);
                if(this->guide.getDescriptions().find(token) != this->guide.getDescriptions().end())
                {
                    this->guide.getCardInfo(token);
                    this->terminal_handler.clearScreen();
                    this->displayStatus();

                    this->terminal_handler.print(player->getPlayerName() + "'s hand: \n");
                    
                    for(const auto& card : player_cards)
                    {
                        terminal_handler.print(card, false);
                    }

                    this->terminal_handler.print("\nSelect a card to play: ");       
                }
                else
                {
                    this->terminal_handler.print("\nInvalid command!");
                }
            }
        }
        else
        {
            this->terminal_handler.print("\nInvalid card! Please select an available card to play.");
        }
    }    

    if (cardName == "Scarecrow")
    {
        for (std::shared_ptr<Card> card : player->getCard())
        {
            if (card->getCardName() == cardName)
            {
                card->use(player, terminal_handler);
                break;
            }
        }
    }
    else if (cardName == "Winter" || cardName == "Spring")
    {
        for (std::shared_ptr<Card> card : player->getCard())
        {
            if (card->getCardName() == cardName)
            {
                this->setSeason(std::dynamic_pointer_cast<Special>(card));
                break;
            }
        }
        player->playCard(cardName, false);
    }
    else if (cardName == "pass")
    {
        player->setPlayerPassed(true);
        this->passCounter++;
        this->lastPlayerPassed = player;
        return;
    }
    player->playCard(cardName);
}

void Match::setWarLand()
{
    terminal_handler.print(this->warSign->getOwner()->getPlayerName() + ", You shall choose a land for war :\n");
    std::unordered_set<std::string> remaining_lands;
    for (std::shared_ptr<Land> land : this->lands)
    {
        if (land->getLandOwner() == nullptr)
        {
           remaining_lands.emplace(land->getLandName());
        }
    }

    for(const auto& land : remaining_lands)
    {
        terminal_handler.print(land, false);
    }

    terminal_handler.print("");
    std::string landName;

    while(true){
        terminal_handler.input(landName);

        if(remaining_lands.find(landName) != remaining_lands.end())
        {
            break;
        }
        terminal_handler.print("\nInvalid Land! Please select one of available lands.");
    }

    int iterator = -1;
    for (std::shared_ptr<Land> land : lands)
    {
        iterator++;
        if (land->getLandName() == landName)
        {
            this->warSign->setLand(land);
            this->lands.erase(this->lands.begin() + iterator);
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
        this->refreshData();
        this->rechargeDeck();
        this->war();
    }
}

void Match::war()
{
    int iterator = this->findStarterPlayer();
    int playersSize = players.size();
    for (iterator; iterator < playersSize; iterator++)
    {
        int tempIterator = iterator;
        if (this->passCounter == playersSize)
        {
            break;
        }
        else if (iterator == playersSize - 1)
        {
            tempIterator = -1;
        }
        if (players[iterator]->getPlayerPassed())
        {
            iterator = tempIterator;
            continue;
        }
        if (players[iterator]->getCard().empty())
        {
            players[iterator]->setPlayerPassed(true);
            this->passCounter++;
            this->lastPlayerPassed = players[iterator];
            iterator = tempIterator;
            continue;
        }

        this->terminal_handler.clearScreen();

        this->terminal_handler.print("Please pass the turn to " + players[iterator]->getPlayerName());
        this->terminal_handler.print("Press any key");

        this->terminal_handler.onClickInput();
        this->terminal_handler.clearScreen();

        this->displayStatus();
        this->playerChoice(players[iterator]);
        this->calculateScore();
        iterator = tempIterator;
    }
    this->stateWinner();
}

void Match::calculateScore()
{
    for (std::shared_ptr<Player> player : players)
    {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        player->setPlayerScore(0);
        for (std::shared_ptr<Card> card : playedCards)
        {
            if (card->getCardType() == "Soldier")
            {
                card->use(player, terminal_handler);
            }
        }
    }
    if (this->getSeason() != nullptr && this->getSeason()->getCardName() == "Winter")
    {
        std::shared_ptr<Winter> winter = std::dynamic_pointer_cast<Winter>(season);
        winter->use(players, terminal_handler);
    }
    for (std::shared_ptr<Player> player : players)
    {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        for (std::shared_ptr<Card> card : playedCards)
        {
            if (card->getCardName() == "Drummer")
            {
                card->use(player, terminal_handler);
                break;
            }
        }
    }
    if (this->getSeason() != nullptr && this->getSeason()->getCardName() == "Spring")
    {
        std::shared_ptr<Spring> spring = std::dynamic_pointer_cast<Spring>(season);
        spring->use(players, terminal_handler);
    }
    for (std::shared_ptr<Player> player : players)
    {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        for (std::shared_ptr<Card> card : playedCards)
        {
            if (card->getCardName() == "Heroine")
            {
                card->use(player, terminal_handler);
            }
        }
    }
}

void Match::stateWinner()
{
    std::shared_ptr<Player> winner = std::make_shared<Player>("temp", 1, "test");
    for (std::shared_ptr<Player> player : players)
    {
        if (player->getPlayerScore() > winner->getPlayerScore())
        {
            winner = player;
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
        this->gameWinner(winner);
    }
    else
    {
        this->warSign->setOwner(this->lastPlayerPassed);
        this->lands.emplace_back(this->warSign->getLand());
    }
}

/// TODO: Decide on making it return bool instead of void
void Match::gameWinner(std::shared_ptr<Player> p_winner)
{
    if (p_winner->getPlayerLandsCount() == 5)
    {
        this->terminal_handler.print(p_winner->getPlayerName() + ", has won!");
        this->is_match_over = true;
        return;
    }
    if (p_winner->getPlayerLandsCount() >= 3)
    {
        for (std::vector<std::shared_ptr<Land>> list : this->adjacentList)
        {
            if (list[0]->getLandOwner()->getPlayerName() == p_winner->getPlayerName() && list[1]->getLandOwner()->getPlayerName() == p_winner->getPlayerName() && list[2]->getLandOwner()->getPlayerName() == p_winner->getPlayerName())
            {
                this->is_match_over = true;
                return;
            }
        }
    }
}
