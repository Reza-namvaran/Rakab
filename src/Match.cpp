#include "Match.hpp"

Match::Match(std::shared_ptr<Storage> database) : deck(std::make_shared<CardDeck>()), warSign(std::make_shared<WarSign>()), peace_sign(std::make_shared<PeaceSign>()), database(database), match_state(1)
{
    status = 0;
    this->playerTurn=-1;
    this->lands = {
        std::make_shared<Land>("ELINIA", (Rectangle){330, 170, 80, 200}),
        std::make_shared<Land>("ROLLO", (Rectangle){425, 655, 230, 85}),
        std::make_shared<Land>("TALMONE", (Rectangle){430, 280, 210, 65}),
        std::make_shared<Land>("PLADACI", (Rectangle){775, 175, 113, 285}),
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

Match::Match(std::vector<std::shared_ptr<Player>> p_players) : Match(std::make_shared<Storage>())
{
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

Match::~Match() {
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
    this->lastPlayerPassed = nullptr;
    this->season = nullptr;
    this->peace_sign->setOwner(nullptr);
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

void Match::playerChoice(std::shared_ptr<Player> p_player)
{

    std::vector<std::string> player_cards;

    this->terminal_handler.print(p_player->getPlayerName() + "'s hand: \n");
    for (std::shared_ptr<Card> card : p_player->getCard())
    {
        player_cards.emplace_back(card->getCardName());
    }

    for (const auto &card : player_cards)
    {
        terminal_handler.print(card, false);
    }

    this->terminal_handler.print("\n" + p_player->getPlayerName() + " Please select a card to play: (pass => skip your turns in this war , help => learn game , help -{card name} => read card description)");
    std::string cardName;

    while (true)
    {
        this->terminal_handler.input(cardName);

        if (std::find(player_cards.begin(), player_cards.end(), cardName) != player_cards.end() || cardName == "pass")
        {
            break;
        }
        else if (cardName.find("help") != std::string::npos)
        {
            if (cardName == "help")
            {
                this->guide.getGameRules();
                // this->terminal_handler.clearScreen();
                this->displayStatus();

                this->terminal_handler.print(p_player->getPlayerName() + "'s hand: \n");

                for (const auto &card : player_cards)
                {
                    terminal_handler.print(card, false);
                }

                this->terminal_handler.print("\n" + p_player->getPlayerName() + " Please select a card to play: (pass => skip your turns in this war , help => learn game , help -{card name} => read card description)");
            }
            else
            {
                std::string token = cardName.substr(cardName.find(" ") + 1);
                if (this->guide.getDescriptions().find(token) != this->guide.getDescriptions().end())
                {
                    this->guide.getCardInfo(token);
                    // this->terminal_handler.clearScreen();
                    this->displayStatus();

                    this->terminal_handler.print(p_player->getPlayerName() + "'s hand: \n");

                    for (const auto &card : player_cards)
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
        else if (cardName == "save")
        {
            this->checkSaveStatus(p_player);
        }
        else if (cardName == "exit")
        {
            this->checkSaveStatus(p_player);
            std::exit(1);
        }
        else
        {
            std::string valid_str = this->guide.suggestion(cardName);
            if (valid_str != cardName && valid_str.length() != 0)
            {
                this->terminal_handler.print("Did you mean " + valid_str + "?");
            }
            else
            {
                this->terminal_handler.print("\nInvalid card! Please select an available card to play.");
            }
        }
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
    else if (cardName == "Bishop")
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
        if(this->season->getCardName() == "Winter")
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
    for (std::shared_ptr<Land> land : lands)
    {
        if (land->getLandOwner() == nullptr && CheckCollisionPointRec(GetMousePosition(), land->getBorder()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && peace_sign->getLand() != land)
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
        return;
    }

    // Setting peace land
    for (std::shared_ptr<Land> land : lands)
    {
        if (land->getLandOwner() == nullptr && CheckCollisionPointRec(GetMousePosition(), land->getBorder()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            peace_sign->setLand(land);
            match_state = 3;
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
        if (this->playerTurn == -1)
        {
            this->setPeaceLand();
            this->setWarLand();
            this->refreshData();
            this->rechargeDeck();
        }
        this->war();
    // }
}

void Match::war()
{
    int iterator;
    if (this->playerTurn != -1)
    {
        iterator = this->playerTurn;
        this->playerTurn = -1;
    }
    else
    {
        iterator = this->findStarterPlayer();
    }
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

        // this->terminal_handler.clearScreen();

        this->terminal_handler.print("Please pass the turn to " + players[iterator]->getPlayerName());
        this->terminal_handler.print("Press any key");

        // this->terminal_handler.onClickInput();
        // this->terminal_handler.clearScreen();

        this->displayStatus();
        this->playerChoice(players[iterator]);

        if (players[iterator]->getCard().empty())
        {
            players[iterator]->setPlayerPassed(true);
            this->passCounter++;
            this->lastPlayerPassed = players[iterator];
        }
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
    if (maxCounter < 2)
    {
        winner->addLand(this->warSign->getLand());
        this->warSign->getLand()->setLandOwner(winner->getSign());
        this->setWarSignOwner(winner);
        this->gameWinner(winner);
    }
    else
    {
        this->setWarSignOwner();
        this->lands.emplace_back(this->warSign->getLand());
    }
    this->setPeaceSignOwner();
}

void Match::gameWinner(std::shared_ptr<Player> p_winner)
{
    if (p_winner->getPlayerLandsCount() == 5)
    {
        this->is_match_over = true;
        terminal_handler.print(p_winner->getPlayerName() + ", You Win!");
        return;
    }
    if (p_winner->getPlayerLandsCount() >= 3)
    {
        for (std::vector<std::shared_ptr<Land>> list : this->adjacentList)
        {
            if (list[0]->getLandOwner() == nullptr || list[1]->getLandOwner() == nullptr || list[2]->getLandOwner() == nullptr)
            {
                continue;
            }
            else if (list[0]->getLandOwner()->getPlayerName() == p_winner->getPlayerName() && list[1]->getLandOwner()->getPlayerName() == p_winner->getPlayerName() && list[2]->getLandOwner()->getPlayerName() == p_winner->getPlayerName())
            {
                this->is_match_over = true;
                terminal_handler.print(p_winner->getPlayerName() + ", You Win!");
                return;
            }
        }
    }
}

void Match::Process() {
    switch (match_state)
    {
    case 0:
        setPeaceLand();
        break;

    case 1:
        // War sign
        setWarLand();
    case 4:
        // War
    default:
        break;
    }
}

void Match::Update() {}

void Match::Render() {

    if (match_state >= 0  && match_state <= 3)
    {
        DrawTexture(Map, 300, 150, WHITE);

        for(std::shared_ptr<Land> land : lands)
        {
            if (warSign->getLand() == land)
            {
                DrawTexture(warSign->getIcon(), land->getBorder().x + 50, land->getBorder().y + 50, WHITE);
            }
            else if (peace_sign->getLand() == land)
            {
                DrawTexture(peace_sign->getIcon(), land->getBorder().x + 50, land->getBorder().y + 50, WHITE);
            }
            else if (land->getLandOwner() != nullptr)
            {
                DrawTexture(land->getLandOwner()->getSign()->getIcon(), land->getBorder().x + 50, land->getBorder().y + 50, WHITE);
            }
            else
            {
                DrawRectangleRec(land->getBorder(), (Color){255, 255, 255, 0});
            }
        }
    }
    else if (match_state == 4)
    {
        // Draw Battle ground
        Rectangle back_ground_rect = { 0.0f, 0.0f, (float)war_background.width, (float)war_background.height };

        DrawTexture(war_background, back_ground_rect.x, back_ground_rect.y, WHITE);
    }
}