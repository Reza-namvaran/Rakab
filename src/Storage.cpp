#include "Storage.hpp"

std::deque<std::string> Storage::save_files;

Storage::Storage()
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
        if (card->getCardType() != "Soldier")
        {
            f_write << card->getCardName() << " ";
        }
        else
        {
            std::shared_ptr<Soldier> soldier = std::dynamic_pointer_cast<Soldier>(card);
            f_write << soldier->getCardName() << soldier->getCardScore() << " ";
        }
    }
    f_write << "\n";

    ///  --------------------- Played ---------------------
    for (std::shared_ptr<Card> card : p_player->getCard(false))
    {
        if (card->getCardType() != "Soldier")
        {
            f_write << card->getCardName() << " ";
        }
        else
        {
            std::shared_ptr<Soldier> soldier = std::dynamic_pointer_cast<Soldier>(card);
            f_write << soldier->getCardName() << soldier->getCardScore() << " ";
        }
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

    /// ------------------------ Lands ---------------------------------
    for (auto land : match->lands)
    {
        if (land->getLandOwner() != nullptr)
            f_write << land->getLandName() << " " << land->getLandOwner()->getPlayerName() << "\n";
    }
    /// ----------------------------------------------------------------

    // ------------------------ Pass Status -------------------------
    f_write << match->passCounter << "\n";

    if (match->lastPlayerPassed != nullptr)
        f_write << match->lastPlayerPassed->getPlayerName();
    else
        f_write << "None";
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

std::vector<std::shared_ptr<Card>> Storage::splitAndCapture(const std::string &str) const
{
    std::istringstream iss(str);
    std::string token;

    std::vector<std::shared_ptr<Card>> cards;

    while (iss >> token)
    {
        std::string card_name;
        std::string card_score;

        for (char c : token)
        {
            if (std::isdigit(c))
            {
                card_score += c;
            }
            else
            {
                card_name += c;
            }
        }

        // if (!card_name.empty() && !card_score.empty())
        // {
        //     std::shared_ptr<Soldier> soldier = std::make_shared<Soldier>(card_name, card_score);
        //     cards.emplace_back(soldier);
        // }
        // else
        // {
        //     /// TODO: Finish this section
        // }
    }
}

void Storage::loadMatch(std::shared_ptr<Match> match, const std::string &path) const
{
    std::ifstream f_read(path);

    if (!f_read.is_open())
    {
        std::cerr << "Error opening the file: " << path << std::endl;
        return;
    }

    std::string line;
    int player_count = 3;

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

        std::getline(f_read, line);

        std::vector<std::shared_ptr<Card>> hand_cards = this->splitAndCapture(line);

        std::getline(f_read, line);

        std::vector<std::shared_ptr<Card>> played_cards = this->splitAndCapture(line);

        new_player->addCard(hand_cards, true);
        new_player->addCard(played_cards, false);

        /// TODO: loadPlayerLands

        match->players.emplace_back(new_player);
    }

    f_read >> player_name >> land;

    if (player_name != "None" && land != "None")
    {
        /// IMPORTANT: Check the logic
        match->warSign->setOwner(std::make_shared<Player>(player_name, 1, "tmp"));
        match->warSign->setLand(std::make_shared<Land>(land));
    }

    /// TODO: Peace sign

    f_read >> season;

    /// IMPORTANT: Check the logic
    // match->season = std::make_shared<Special>(season);

    f_read >> pass_counter;
    match->passCounter = pass_counter;

    f_read >> player_name;

    /// IMPORTANT: Check the logic
    match->lastPlayerPassed = std::make_shared<Player>(player_name, 1, "tmp");
}
