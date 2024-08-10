#include "Storage.hpp"

std::deque<std::string> Storage::save_files;

Storage::Storage() : deck(std::make_shared<CardDeck>())
{
    if (!std::filesystem::exists("data/"))
    {
        /// NOTE: if file save folder isn't available this will create it
        std::filesystem::create_directory("data/");
    }
    for (const auto &file : std::filesystem::directory_iterator("data/"))
    {
        if (file.is_regular_file())
        {
            this->save_files.push_back("data/" + file.path().filename().string());
        }
    }
}

std::deque<std::string> Storage::getFilesNames() const { return this->save_files; }

/// DESCRIPTION: this method is used for generating name for save files using the time of the save action
std::string Storage::generateFileName() const
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    std::ostringstream out;
    out << "data/" << "rakab_" << std::put_time(std::localtime(&time_t), "%Y%m%d%H%M%S") << ".txt";
    return out.str();
}

/// DESCRIPTION: this method writes player related data in the save file
void Storage::savePlayerInfo(std::shared_ptr<Player> p_player, const std::string &path) const
{
    std::ofstream f_write(path, std::ios_base::app);

    if (!f_write.is_open())
    {
        std::cerr << "Error opening file: " << path << std::endl;
        return;
    }

    /// --------------- Player general data -----------------------
    f_write << p_player->getPlayerName() << " " << p_player->getPlayerAge() << " " << p_player->getSign()->getColor()
            << " " << p_player->getPlayerScore() << " " << p_player->getPlayerPassed() << "\n";
    /// -----------------------------------------------------------

    /// IMPORTANT: Do something about score of soldiers!

    /// -------------------- Player Cards -----------------------------
    ///  ---------------------  In hand ---------------------
    for (std::shared_ptr<Card> card : p_player->getCard())
    {
        f_write << card->getCardName() << " ";
    }
    f_write << "\n";

    ///  --------------------- Played ---------------------
    for (std::shared_ptr<Card> card : p_player->getCard(false))
    {
        f_write << card->getCardName() << " ";
    }
    f_write << "\n";
    /// ---------------------------------------------------------------

    /// ---------------------- Player lands ------------------------------
    for (std::shared_ptr<Land> land : p_player->getSign()->getLands())
    {
        f_write << land->getLandName() << " ";
    }
    f_write << "\n";

    /// ------------------------------------------------------------------

    f_write.close();
}

/// DESCRIPTION: This method saves match essential data (other than players) to the save files
void Storage::saveMatchInfo(std::shared_ptr<Match> match, const std::string &path, std::shared_ptr<Player> playerTurn) const
{
    std::ofstream f_write(path, std::ios_base::app);

    if (!f_write.is_open())
    {
        std::cerr << "Error opening " << path << std::endl;
        return;
    }

    // --------------------------------- War and Peace Signs --------------------------------
    f_write << playerTurn->getPlayerName() << "\n";
    if (match->warSign->getOwner() != nullptr)
        f_write << match->warSign->getOwner()->getPlayerName() << " " << match->warSign->getLand()->getLandName() << "\n";
    else
        f_write << "None" << " None" << "\n";

    if (match->peace_sign->getLand() != nullptr)
        f_write << match->peace_sign->getLand()->getLandName() << "\n";
    else
        f_write << "None" << "\n";

    if (match->peace_sign->getOwner() != nullptr)
        f_write << match->peace_sign->getOwner()->getPlayerName() << "\n";
    else
        f_write << "None" << "\n";
    // we could have war sign without peace sign

    // --------------------------------------------------------------------------------------

    /// -------------- Season -----------------
    if (match->getSeason() != nullptr)
        f_write << match->getSeason()->getCardName() << "\n";
    else
        f_write << "None" << "\n";
    /// ---------------------------------------

    /// ----------------------------------------------------------------

    // ------------------------ Pass Status -------------------------
    f_write << match->passCounter << "\n";

    // ---------------------------------------------------------------

    // -------------- Last Played who played Bishop ------------------
    if (match->lastPlayerPassed != nullptr)
        f_write << match->lastPlayerPassed->getPlayerName() << "\n";
    else
        f_write << "None" << "\n";
    // --------------------------------------------------------------

    // -------------------- match_state -----------------------------
    f_write << 3 << "\n";
    // --------------------------------------------------------------

    // -------------------- Hand Card Position ----------------------

    for (size_t idx = 0; idx < match->handsCardPos.size(); ++idx)
    {   if (idx != match->handsCardPos.size() - 1)
            f_write << match->handsCardPos[idx].x << " " << match->handsCardPos[idx].y << " " << match->handsCardPos[idx].width << match->handsCardPos[idx].height << "\n";
        else
            f_write << match->handsCardPos[idx].x << " " << match->handsCardPos[idx].y << " " << match->handsCardPos[idx].width << match->handsCardPos[idx].height;
    }

    // --------------------------------------------------------------

    f_write.close();
}

/// DESCRIPTION: this method saves constructs a complete save file
void Storage::saveNewGame(std::shared_ptr<Match> match, std::shared_ptr<Player> playerTurn)
{
    /// NOTE: Use ring buffer logic to re-write first game after 5 games
    if (save_files.size() == 5)
    {
        std::filesystem::remove(save_files.front());
        save_files.pop_front();
    }

    std::string new_file_name = this->generateFileName();

    std::ofstream f_write(new_file_name);

    if (!f_write.is_open())
    {
        std::cerr << "Cannot open the file" << std::endl;
    }

    f_write << match->players.size() << "\n";

    f_write.close();

    for (auto player : match->players)
    {
        savePlayerInfo(player, new_file_name);
    }

    saveMatchInfo(match, new_file_name, playerTurn);

    save_files.push_back(new_file_name);
}

std::vector<std::shared_ptr<Card>> Storage::splitAndCaptureCards(const std::string &str)
{
    std::istringstream iss(str);
    std::string cardName;

    std::vector<std::shared_ptr<Card>> cards;
    this->deck->generateDeck();
    std::vector<std::shared_ptr<Card>> tempDeck = this->deck->getDeck();

    while (iss >> cardName)
    {
        for (std::shared_ptr<Card> card : tempDeck)
        {
            if (card->getCardName() == cardName)
            {
                cards.push_back(card);
                break;
            }
        }
    }
    return cards;
}

std::vector<std::shared_ptr<Land>> Storage::splitAndCaptureLands(const std::string &str, std::shared_ptr<Match> match)
{
    std::istringstream iss(str);
    std::string landName;

    std::vector<std::shared_ptr<Land>> lands;

    while (iss >> landName)
    {
        for (std::shared_ptr<Land> land : match->lands)
        {
            if (land->getLandName() == landName)
            {
                lands.push_back(land);
                break;
            }
        }
    }
    return lands;
}

Rectangle Storage::splitAndCaptureRecs(const std::string &str)
{
    std::istringstream iss(str);
    Rectangle rect;

    iss >> rect.x >> rect.y >> rect.width >> rect.height;

    return rect;
}

void Storage::loadMatch(std::shared_ptr<Match> match, const std::string &path)
{
    std::ifstream f_read(path);

    if (!f_read.is_open())
    {
        std::cerr << "Error opening the file: " << path << std::endl;
        return;
    }

    std::string line;
    int player_count;

    f_read >> player_count;
    std::string player_name, player_color, season, land;
    int player_age, player_score, pass_counter;
    bool is_passed;

    for (int idx = 0; idx < player_count; ++idx)
    {
        f_read >> player_name >> player_age >> player_color >> player_score >> is_passed;
        std::shared_ptr<Player> new_player = std::make_shared<Player>(player_name, player_age, player_color);
        new_player->setPlayerPassed(is_passed);
        new_player->setPlayerScore(player_score);

        f_read.ignore();
        std::getline(f_read, line);

        std::vector<std::shared_ptr<Card>> hand_cards = this->splitAndCaptureCards(line);

        std::getline(f_read, line);

        std::vector<std::shared_ptr<Card>> played_cards = this->splitAndCaptureCards(line);

        new_player->addCard(hand_cards, true);
        new_player->addCard(played_cards, false);

        std::getline(f_read, line);

        std::vector<std::shared_ptr<Land>> played_lands = this->splitAndCaptureLands(line, match);

        for (std::shared_ptr<Land> land : played_lands)
        {
            new_player->addLand(land);
        }

        match->players.emplace_back(new_player);
    }

    f_read >> player_name;
 
    for (int iterator = 0; iterator < match->players.size(); iterator++)
    {
        if (player_name == match->players[iterator]->getPlayerName())
        {
            match->loadPlayerTurn = iterator;
            break;
        }
    }
    f_read >> player_name >> land;

    if (player_name != "None" && land != "None")
    {
        for (std::shared_ptr<Player> player : match->players)
        {
            if (player_name == player->getPlayerName())
            {
                match->warSign->setOwner(player);
                break;
            }
        }

        for (std::shared_ptr<Land> landPtr : match->lands)
        {
            if (land == landPtr->getLandName())
            {
                match->warSign->setLand(landPtr);
                break;
            }
        }
    }

    f_read >> player_name >> land;
    if (player_name != "None")
    {
        for (std::shared_ptr<Player> player : match->players)
        {
            if (player_name == player->getPlayerName())
            {
                match->peace_sign->setOwner(player);
                break;
            }
        }
    }
    if (land != "None")
    {
        for (std::shared_ptr<Land> landPtr : match->lands)
        {
            if (land == landPtr->getLandName())
            {
                match->peace_sign->setLand(landPtr);
                break;
            }
        }
    }

    f_read >> season;

    if (season == "Spring")
    {
        match->season = std::make_shared<Spring>(season);
    }
    else
    {
        match->season = std::make_shared<Winter>(season);
    }

    f_read >> pass_counter;
    match->passCounter = pass_counter;

    f_read >> player_name;

    for (std::shared_ptr<Player> player : match->players)
    {
        if (player_name == player->getPlayerName())
        {
            match->lastPlayerPassed = player;
            break;
        }
    }

    int matchState;
    f_read >> matchState;
    match->match_state = matchState;

    std::vector<Rectangle> positions;
    f_read.ignore();
    while(std::getline(f_read, line))
    {
        Rectangle pos = splitAndCaptureRecs(line);
        positions.push_back(pos);
    }

    match->handsCardPos = positions;

    f_read.close();
    
}
