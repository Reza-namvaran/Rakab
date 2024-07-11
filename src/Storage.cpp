#include "Storage.hpp"

Storage::Storage() {
    if (!std::filesystem::exists(SAVE_FOLDER))
    {
        /// NOTE: if file save folder isn't available this will create it
        std::filesystem::create_directory(SAVE_FOLDER);
    }
}

/// DESCRIPTION: this method is used for generating name for save files using the time of the save action
std::string Storage::generateFileName() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::ostringstream out;
    out <<  SAVE_FOLDER << SAVE_FILE_PREFIX << std::put_time(std::localtime(&time_t), "%Y%m%d%H%M%S") << SAVE_FILE_EXTENSION;
    return out.str();
}

/// DESCRIPTION: this method writes player related data in the save file
void Storage::savePlayerInfo(std::shared_ptr<Player> p_player,const std::string& path) const {
    std::ofstream f_write(path, std::ios_base::app);

    if(!f_write.is_open())
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
    for(std::shared_ptr<Card> card : p_player->getCard())
    {
        if(card->getCardType() != "Soldier")
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
    for(std::shared_ptr<Card> card : p_player->getCard(false))
    {
        if(card->getCardType() != "Soldier")
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
    for(std::shared_ptr<Land> land : p_player->getSign()->getLands())
    {
        f_write << land->getLandName() << " ";
    }
    f_write << "\n";

    /// ------------------------------------------------------------------

    f_write.close();
}

/// DESCRIPTION: This method saves match essential data (other than players) to the save files
void Storage::saveMatchInfo(std::shared_ptr<Match> match, const std::string& path) const {
    std::ofstream f_write(path, std::ios_base::app);

    if (!f_write.is_open())
    {
        std::cerr << "Error opening " << path <<  std::endl;
        return;
    }

    // --------------------------------- War and Peace Signs --------------------------------
    f_write << match->warSign->getOwner() << " " << match->warSign->getLand() << "\n";
    f_write << match->peace_sign->getOwner() << " " << match->peace_sign->getLand() << "\n";
    // --------------------------------------------------------------------------------------
    
    /// -------------- Season -----------------
    f_write << match->getSeason() << "\n";
    /// ---------------------------------------

    /// ------------------------ Lands ---------------------------------
    for (auto land : match->lands)
    {
        f_write << land->getLandName() << " " << land->getLandOwner()->getPlayerName() << "\n";
    }
    /// ----------------------------------------------------------------

    // ------------------------ Pass Status -------------------------
    f_write << match->passCounter << "\n";
    f_write << match->lastPlayerPassed << "\n";
    // --------------------------------------------------------------

    f_write.close();
}

/// DESCRIPTION: this method saves constructs a complete save file
void Storage::saveNewGame(std::shared_ptr<Match> match) {
    /// NOTE: Use ring buffer logic to re-write first game after 5 games
    if (save_files.size() == MAX_SAVES)
    {
        std::filesystem::remove(save_files.front());
        save_files.pop_front();
    }

    std::string new_file_name = this->generateFileName();

    for(auto player : match->players)
    {
        savePlayerInfo(player, new_file_name);
    }

    saveMatchInfo(match, new_file_name);

    save_files.push_back(new_file_name);
}