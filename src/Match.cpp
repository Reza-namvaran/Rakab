#include "Match.hpp"

Match::Match() : deck(std::make_shared<CardDeck>()), warSign(std::make_shared<WarSign>()), peace_sign(std::make_shared<PeaceSign>()), database(std::make_shared<Storage>()), loadPlayerTurn(-1), playerTurn(-1)
{
    status = 0;
    this->lands = {
        std::make_shared<Land>("ELINIA", (Rectangle){330, 170, 80, 200}),
        std::make_shared<Land>("ROLLO", (Rectangle){425, 165, 230, 85}),
        std::make_shared<Land>("TALMONE", (Rectangle){430, 280, 210, 65}),
        std::make_shared<Land>("PLADACI", (Rectangle){775, 175, 113, 110}),
        std::make_shared<Land>("MORINA", (Rectangle){645, 290, 140, 110}),
        std::make_shared<Land>("ARMENTO", (Rectangle){585, 460, 70, 75}),
        std::make_shared<Land>("LIA", (Rectangle){590, 645, 90, 70}),
        std::make_shared<Land>("OLIVADI", (Rectangle){700, 550, 60, 165}),
        std::make_shared<Land>("BORGE", (Rectangle){805, 340, 95, 150}),
        std::make_shared<Land>("DIMASE", (Rectangle){765, 505, 135, 205}),
        std::make_shared<Land>("BELLA", (Rectangle){890, 175, 175, 130}),
        std::make_shared<Land>("CALINE", (Rectangle){905, 310, 160, 80}),
        std::make_shared<Land>("ENNA", (Rectangle){910, 415, 105, 125}),
        std::make_shared<Land>("ATELA", (Rectangle){910, 560, 160, 55})};
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

    Map = LoadTexture("../assets/pics/Map.png");

    war_background = LoadTexture("../assets/pics/background.png");
    winter_background = LoadTexture("../assets/pics/winter_bkg.png");
    spring_background = LoadTexture("../assets/pics/spring_bkg.png");
}

Match::Match(std::vector<std::shared_ptr<Player>> p_players) : Match()
{
    match_state = 1;
    status = 0;
    this->players = p_players;
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

Match::~Match()
{
    UnloadTexture(Map);
}

void Match::displayStatus()
{

    /* First field of status -> players' score + played cards */
    std::string separator(50, '-');

    this->terminal_handler.print(separator);

    for (std::shared_ptr<Player> player : this->players)
    {
        if (!player->getPlayerPassed())
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

    /* Third field -> current land and season */

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

void Match::resetMatchstatus() { this->is_match_over = false; }

void Match::dealCardsToPlayers()
{
    for (std::shared_ptr<Player> player : this->players)
    {
        this->deck->dealCard(player);
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
    this->playerTurn = -1;
    this->lastPlayerBishoped = nullptr;
    this->lastPlayerPassed = nullptr;
    this->sleipnirPlayed = false;
    this->season = nullptr;
    war_background = LoadTexture("../assets/pics/background.png");
    for (std::shared_ptr<Player> player : players)
    {
        player->resetPlayerData();
    }
}

unsigned int Match::findStarterPlayer() const
{
    int i = 0;
    if (this->playerTurn == -1)
    {
        for (i; i < players.size(); i++)
        {
            if ((this->lastPlayerWon != nullptr && players[i]->getPlayerName() == this->lastPlayerWon->getPlayerName()) || (players[i]->getPlayerName() == warSign->getOwner()->getPlayerName() && this->lastPlayerWon == nullptr))
            {
                break;
            }
        }
    }
    else
    {
        i = this->playerTurn + 1;
        if (i == players.size())
        {
            i = 0;
        }
    }
    return i;
}

void Match::playerChoice(std::shared_ptr<Player> p_player)
{
    this->match_state = 4;
    std::string cardName;
    int iterator = 0;
    for (Rectangle cardPos : this->handsCardPos)
    {
        if (CheckCollisionPointRec(GetMousePosition(), cardPos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            cardName = p_player->getCard()[iterator]->getCardName();
            this->match_state = 3;
            break;
        }
        iterator++;
    }
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){1220, 800, 100, 60}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        cardName = "pass";
        this->match_state = 3;
    }
    if (players[this->playerTurn]->getPlayerPassed())
    {
        this->match_state = 3;
        return;
    }
    if (players[this->playerTurn]->getCard().empty())
    {
        players[this->playerTurn]->setPlayerPassed(true);
        this->passCounter++;
        this->lastPlayerPassed = players[this->playerTurn];
        this->match_state = 3;
        return;
    }
    if (cardName == "Scarecrow")
    {
        for (std::shared_ptr<Card> card : p_player->getCard())
        {
            if (card->getCardName() == cardName)
            {
                card->use(p_player, terminal_handler);
                break;
            }
        }
    }
    // else
    if (cardName == "Bishop")
    {
        this->lastPlayerBishoped = p_player;
    }
    else if (cardName == "Winter" || cardName == "Spring")
    {
        for (std::shared_ptr<Card> card : p_player->getCard())
        {
            if (card->getCardName() == cardName)
            {
                this->setSeason(std::dynamic_pointer_cast<Special>(card));
                break;
            }
        }
        p_player->playCard(cardName, false);
        if (this->season->getCardName() == "Winter")
        {
            war_background = winter_background;
        }
        else if (this->season->getCardName() == "Spring")
        {
            war_background = spring_background;
        }
        /// TODO: Add reset to normal
        return;
    }
    else if (cardName == "Turncoat")
    {
        for (std::shared_ptr<Card> card : p_player->getCard())
        {
            if (card->getCardName() == cardName)
            {
                std::shared_ptr<Turncoat> turncoat = std::dynamic_pointer_cast<Turncoat>(card);
                turncoat->use(this->players, this->lastPlayerPassed, this->warSign, this->passCounter);
                break;
            }
        }
    }
    else if (cardName == "Mirage")
    {
        for (std::shared_ptr<Card> card : p_player->getCard())
        {
            if (card->getCardName() == cardName)
            {
                std::shared_ptr<Mirage> mirage = std::dynamic_pointer_cast<Mirage>(card);
                mirage->use(players[playerTurn], terminal_handler);
                break;
            }
        }
    }
    else if (cardName == "WhiteSeal")
    {
        for (std::shared_ptr<Card> card : p_player->getCard())
        {
            if (card->getCardName() == cardName)
            {
                p_player->playCard(cardName);
                std::shared_ptr<WhiteSeal> whiteseal = std::dynamic_pointer_cast<WhiteSeal>(card);
                whiteseal->use(players);
                return;
            }
        }
    }
    else if (cardName == "Sleipnir")
    {
        for (std::shared_ptr<Card> card : p_player->getCard())
        {
            if (card->getCardName() == cardName)
            {
                std::shared_ptr<Sleipnir> sleipnir = std::dynamic_pointer_cast<Sleipnir>(card);
                sleipnir->use(players, this->sleipnirPlayed, passCounter);
                warSign->setOwner(players[playerTurn]);
                break;
            }
        }
    }
    else if (cardName == "pass")
    {
        p_player->setPlayerPassed(true);
        this->passCounter++;
        this->lastPlayerPassed = p_player;
        return;
    }
    p_player->playCard(cardName);
}

void Match::setWarSignOwner(std::shared_ptr<Player> p_player)
{
    if (p_player == nullptr)
        p_player = this->lastPlayerPassed;
    unsigned int max = 0;
    std::shared_ptr<Player> warSignOwner;
    for (std::shared_ptr<Player> player : this->players)
    {
        unsigned int maxCounter = 0;
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        for (std::shared_ptr<Card> card : playedCards)
        {
            if (card->getCardName() == "Spy")
            {
                maxCounter++;
            }
        }
        for (std::shared_ptr<Player> player : players)
        {
            for (std::shared_ptr<Card> card : player->getCard(false))
            {
                if (card->getCardName() == "Turncoat")
                {
                    return;
                }
            }
        }
        if (maxCounter > max)
        {
            max = maxCounter;
            warSignOwner = player;
        }
    }
    if (max != 0)
        p_player = warSignOwner;
    this->warSign->setOwner(p_player);
}

void Match::setPeaceSignOwner()
{
    unsigned int max = 0;
    std::shared_ptr<Player> peaceSignOwner = nullptr;
    for (std::shared_ptr<Player> player : this->players)
    {
        unsigned int maxCounter = 0;
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        for (std::shared_ptr<Card> card : playedCards)
        {
            if (card->getCardName() == "Bishop")
            {
                maxCounter++;
            }
        }
        if (maxCounter > max)
        {
            max = maxCounter;
            peaceSignOwner = player;
        }
        else if (maxCounter == max)
        {
            peaceSignOwner = this->lastPlayerBishoped;
        }
    }
    this->peace_sign->setOwner(peaceSignOwner);
}

void Match::setWarLand()
{
    // Setting war land
    std::vector<std::shared_ptr<Land>> owneredLands;
    for (std::shared_ptr<Player> player : this->players)
    {
        for (std::shared_ptr<Land> land : player->getSign()->getLands())
        {
            owneredLands.push_back(land);
        }
    }

    for (std::shared_ptr<Land> land : lands)
    {
        if (land->getLandOwner() == nullptr && CheckCollisionPointRec(GetMousePosition(), land->getBorder()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && peace_sign->getLand() != land)
        if (std::find(owneredLands.begin(), owneredLands.end(), land) == owneredLands.end() && CheckCollisionPointRec(GetMousePosition(), land->getBorder()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && peace_sign->getLand() != land)
        {
            warSign->setLand(land);
            match_state = 3;
            break;
        }
    }
}

void Match::setPeaceLand()
{
    /// NOTE: In case that no one played Bishop in a war
    if (this->peace_sign->getOwner() == nullptr)
    {
        match_state = 1;
        return;
    }

    // Setting peace land
    for (std::shared_ptr<Land> land : lands)
    {
        if (land->getLandOwner() == nullptr && CheckCollisionPointRec(GetMousePosition(), land->getBorder()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            peace_sign->setLand(land);
            match_state = 2;
            break;
        }
    }
}

void Match::checkSaveStatus(std::shared_ptr<Player> player_turn)
{
    std::shared_ptr<Match> save_instance = std::make_shared<Match>(*this);
    this->database->saveNewGame(save_instance, player_turn);
}

void Match::run()
{
    // while (!this->is_match_over)
    // {
    // this->terminal_handler.clearScreen();
    if (this->loadPlayerTurn == -1)
    {
        // this->setPeaceLand();
        // this->setWarLand();
        this->refreshData();
        this->rechargeDeck();
    }
    // this->war();
    // }
}

void Match::war()
{
    if (this->loadPlayerTurn != -1)
    {
        this->playerTurn = this->loadPlayerTurn;
        this->loadPlayerTurn = -1;
    }
    int playersSize = players.size();
    if (this->passCounter == playersSize)
    {
        this->match_state = 6;
        return;
    }
    if (players[this->playerTurn]->getPlayerPassed())
    {
        this->match_state = 3;
        return;
    }
    if (players[this->playerTurn]->getCard().empty())
    {
        players[this->playerTurn]->setPlayerPassed(true);
        this->passCounter++;
        this->lastPlayerPassed = players[this->playerTurn];
        this->match_state = 3;
        return;
    }

    // this->terminal_handler.clearScreen();

    // this->terminal_handler.onClickInput();
    // this->terminal_handler.clearScreen();

    // this->displayStatus();
    // this->playerChoice(players[this->playerTurn]);

    this->calculateScore();
    // this->stateWinner();
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
            }
        }
    }
    if (this->getSeason() != nullptr && this->getSeason()->getCardName() == "Spring")
    {
        std::shared_ptr<Spring> spring = std::dynamic_pointer_cast<Spring>(season);
        spring->use(players, terminal_handler);
    }
    /// NOTE: Calculate score for Heroine and Spy
    for (std::shared_ptr<Player> player : players)
    {
        std::vector<std::shared_ptr<Card>> playedCards = player->getCard(false);
        for (std::shared_ptr<Card> card : playedCards)
        {
            if (card->getCardName() == "Heroine" || card->getCardName() == "Spy")
            {
                card->use(player, terminal_handler);
            }
        }
    }
}

void Match::stateWinner()
{
    for (std::shared_ptr<Player> player : players)
    {
        for (std::shared_ptr<Card> card : player->getCard(false))
        {
            if (card->getCardName() == "Bishop")
            {
                std::shared_ptr<Bishop> bishop = std::dynamic_pointer_cast<Bishop>(card);
                bishop->use(this->players);
            }
        }
    }
    this->calculateScore();
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
    if (this->sleipnirPlayed)
    {
        for (std::shared_ptr<Player> player : players)
        {
            for (std::shared_ptr<Card> card : player->getCard(false))
            {
                if (card->getCardName() == "Sleipnir")
                {
                    winner = player;
                    break;
                }
            }
            if (winner == player)
            {
                break;
            }
        }
        winner->addLand(this->warSign->getLand());
        this->warSign->getLand()->setLandOwner(winner->getSign());
        this->warSign->setOwner(winner);
        this->gameWinner(winner);
        lastPlayerWon = winner;
    }

    if (maxCounter < 2)
    {
        winner->addLand(this->warSign->getLand());
        this->warSign->getLand()->setLandOwner(winner->getSign());

        // std::clog << warSign->getLand()->getLandOwner()->getPlayerName() << "546468468464684656486" << std::endl;
        this->setWarSignOwner(winner);
        this->gameWinner(winner);
        lastPlayerWon = winner;
    }
    else
    {
        lastPlayerWon = nullptr;
        this->setWarSignOwner();
        this->lands.emplace_back(this->warSign->getLand());
    }
    if (match_state != 8)
        this->setPeaceSignOwner();
}

void Match::gameWinner(std::shared_ptr<Player> p_winner)
{
    if (p_winner->getPlayerLandsCount() == 5)
    {
        this->is_match_over = true;
        terminal_handler.print(p_winner->getPlayerName() + ", You Win!");
        this->winnerOfTheGame = p_winner;
        this->match_state = 8;
        return;
    }
    if (p_winner->getPlayerLandsCount() >= 3)
    {
        for (std::vector<std::shared_ptr<Land>> list : this->adjacentList)
        {
            for (std::shared_ptr<Land> land : list)
            {
                if (land->getLandOwner() != nullptr)
                    std::clog << land->getLandName() << std::endl;
            }
            // if (list[0]->getLandOwner() == nullptr || list[1]->getLandOwner() == nullptr || list[2]->getLandOwner() == nullptr)
            // {
            //     continue;
            // }
            // else if (list[0]->getLandOwner()->getPlayerName() == p_winner->getPlayerName() && list[1]->getLandOwner()->getPlayerName() == p_winner->getPlayerName() && list[2]->getLandOwner()->getPlayerName() == p_winner->getPlayerName())
            // {
            //     this->is_match_over = true;
            //     terminal_handler.print(p_winner->getPlayerName() + ", You Win!");
            //     this->winnerOfTheGame = p_winner;
            //     this->match_state = 8;
            //     return;
            // }
            std::vector<std::shared_ptr<Land>> lands = p_winner->getSign()->getLands();
            if (std::find(lands.begin(), lands.end(), list[0]) != lands.end() && std::find(lands.begin(), lands.end(), list[1]) != lands.end() && std::find(lands.begin(), lands.end(), list[2]) != lands.end())
            {
                this->is_match_over = true;
                terminal_handler.print(p_winner->getPlayerName() + ", You Win!");
                this->winnerOfTheGame = p_winner;
                this->match_state = 8;
                return;
            }
        }
    }
}

void Match::Process()
{
    std::clog << "-------------------- in Match Process ------------------" << std::endl;
    std::clog << match_state << std::endl;
    if (match_state == 0)
    {
        setPeaceLand();
    }
    if (match_state == 2)
    {
        this->peace_sign->setOwner(nullptr);
        match_state = 1;
    }
    if (match_state == 1)
    {
        setWarLand();
    }
    if (match_state == 3)
    {
        if (this->playerTurn == -1 && this->loadPlayerTurn == -1)
            this->rechargeDeck();
        this->playerTurn = this->findStarterPlayer();
        this->war();
    }
    if (match_state == 4)
    {
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){1000, 0, 100, 60}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            std::clog << match_state << " Enter 5" << std::endl;
            this->match_state = 5;
            guide.setStatus(5);
            std::clog << match_state << std::endl;
        }
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){1150, 0, 100, 60}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            this->match_state = 9;
            std::clog << match_state << std::endl;
        }
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){1295, 0, 100, 60}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            this->checkSaveStatus(players[playerTurn]);
        }
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){0, 0, 85, 40}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            status = 2;
        }
    }
    if (match_state == 5)
    {
        // Game rules guideline
        match_state = guide.getStatus();
    }
    if (match_state == 6)
    {
        // war winner
        this->stateWinner();
        this->refreshData();
        if (match_state != 8)
            this->match_state = 7;
    }
    if (match_state == 7)
    {
        // select next
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){1000, 800, 100, 60}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            match_state = 0;
        }
    }
    if (match_state == 8)
    {
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){1000, 800, 100, 60}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            status = 2;
        }
    }
    if (match_state == 9)
    {
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){1000, 0, 100, 60}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            this->match_state = 4;
        }
    }
}

void Match::Update()
{
    if (match_state == 3 || match_state == 4)
    {
        this->playerChoice(this->players[this->playerTurn]);
    }
    if (match_state == 5)
    {
        this->guide.getGuidline();
    }
}

void Match::Render()
{
    if (match_state >= 0 && match_state <= 2 || match_state == 9)
    {
        DrawTexture(Map, 300, 150, WHITE);
        DrawText(warSign->getOwner()->getPlayerName().c_str(), 1150, 810, 30, BLACK);
        if (peace_sign->getOwner() != nullptr)
            DrawText(peace_sign->getOwner()->getPlayerName().c_str(), 1150, 830, 30, BLACK);

        for (std::shared_ptr<Land> land : lands)
        {
            if (warSign->getLand() == land)
            {
                DrawTexture(warSign->getIcon(), land->getBorder().x + 30, land->getBorder().y + 30, WHITE);
            }
            else if (peace_sign->getLand() == land)
            {
                DrawTexture(peace_sign->getIcon(), land->getBorder().x + 30, land->getBorder().y + 30, WHITE);
            }
            // else if (land->getLandOwner() != nullptr)
            // {
            //     DrawTexture(land->getLandOwner()->getSign()->getIcon(), land->getBorder().x + 30, land->getBorder().y + 30, WHITE);
            // }
            else
            {
                DrawRectangleRec(land->getBorder(), (Color){255, 255, 255, 0});
            }
        }

        for (std::shared_ptr<Player> player : players)
        {
            std::vector<std::shared_ptr<Land>> p_lands = player->getSign()->getLands();
            if (p_lands.size() == 0)
                continue;
            for (std::shared_ptr<Land> p_land : p_lands)
            {
                DrawTexture(player->getSign()->getIcon(), p_land->getBorder().x + 30, p_land->getBorder().y + 30, WHITE);
            }
        }

        if (lastPlayerWon != nullptr)
        {
            std::string p_lands = "";
            for (std::shared_ptr<Land> land : lastPlayerWon->getSign()->getLands())
            {
                p_lands += land->getLandName() + ", ";
            }
            DrawText(p_lands.c_str(), 10, 0, 20, BLACK);
        }
        if (match_state == 9)
        {
            DrawRectangleRec((Rectangle){1000, 0, 100, 60}, GREEN);
            DrawText("Back", 1010, 0, 30, WHITE);
        }
    }
    else if (match_state == 3 || match_state == 4)
    {
        this->handsCardPos.clear();
        // Draw Battle ground
        Rectangle back_ground_rect = {0.0f, 0.0f, (float)war_background.width, (float)war_background.height};
        DrawTexture(war_background, back_ground_rect.x, back_ground_rect.y, WHITE);
        int y = 0;
        for (std::shared_ptr<Player> player : players)
        {
            DrawText(player->getPlayerName().c_str(), 10, 65 + y * 110, 20, WHITE);
            DrawText(std::to_string(player->getPlayerScore()).c_str(), 10, 95 + y * 110, 20, BLACK);
            if (player->getPlayerPassed())
                DrawText("PASSED", 5, 125 + y * 110, 15, GREEN);
            int x = 0;
            for (std::shared_ptr<Card> card : player->getCard(false))
            {
                DrawTexture(card->getCardPic(), 80 + x * 80, 50 + y * 110, WHITE);
                x++;
            }
            y++;
        }

        int i = 0;
        for (std::shared_ptr<Card> card : this->players[this->playerTurn]->getCard())
        {
            DrawTexture(card->getCardPic(), 20 + i * 80, 770, WHITE);
            this->handsCardPos.push_back((Rectangle){(float)(20 + i * 80), 770, 70, 108});
            i++;
        }
        DrawText(this->players[this->playerTurn]->getPlayerName().c_str(), 1300, 865, 30, BLACK);
        DrawText(std::to_string(this->players[this->playerTurn]->getPlayerScore()).c_str(), 1350, 810, 30, WHITE);
        DrawRectangleRec((Rectangle){1220, 800, 100, 60}, WHITE);
        DrawText("PASS", 1230, 815, 30, BLACK);

        DrawRectangleRec((Rectangle){1000, 0, 100, 60}, WHITE);
        DrawText("Help", 1010, 0, 30, BLACK);
        DrawRectangleRec((Rectangle){1150, 0, 100, 60}, GREEN);
        DrawText("Map", 1160, 0, 30, WHITE);
        DrawRectangleRec((Rectangle){1295, 0, 100, 60}, GREEN);
        DrawText("Save", 1295, 0, 30, WHITE);

        DrawRectangleRec((Rectangle){0, 0, 85, 40}, WHITE);
        DrawText("Back", 0, 0, 30, BLACK);
    }
    else if (match_state == 5)
    {
        this->guide.render();
    }
    else if (match_state == 7)
    {
        std::string win_msg = "Tie!";
        if (lastPlayerWon != nullptr)
            win_msg = lastPlayerWon->getPlayerName() + ", You Win!";

        DrawText(win_msg.c_str(), 350, 350, 30, BLACK);

        DrawRectangleRec((Rectangle){1000, 800, 100, 60}, WHITE);
        DrawText("Next", 1010, 815, 30, BLACK);
    }
    else if (match_state == 8)
    {
        std::string win_msg = "Congratulations ";
        if (winnerOfTheGame != nullptr)
            win_msg = win_msg + winnerOfTheGame->getPlayerName() + ", You are the Winner!";

        DrawText(win_msg.c_str(), 350, 350, 30, BLACK);

        DrawRectangleRec((Rectangle){1000, 800, 100, 60}, WHITE);
        DrawText("Next", 1010, 815, 30, BLACK);
    }
}