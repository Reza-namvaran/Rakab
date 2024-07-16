#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <filesystem>
#include <deque> 
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

/// NOTE: using deque as a ring buffer 

#include "Match.hpp"

class Match;

class Storage {
  public:
    Storage();

    ~Storage() = default;

    void saveNewGame(std::shared_ptr<Match> match);

    void load();  

  private:
    const int MAX_SAVES = 5;
    const std::string SAVE_FOLDER = "data/";
    const std::string SAVE_FILE_PREFIX = "rakab_";
    const std::string SAVE_FILE_EXTENSION = ".txt";
    static std::deque<std::string> save_files;

    /// ------------------------ private function members ---------------------------
    void savePlayerInfo(std::shared_ptr<Player> p_player,const std::string& path) const;
    void saveMatchInfo(std::shared_ptr<Match> match, const std::string& path) const;
    std::string generateFileName() const;
    /// -----------------------------------------------------------------------------
};

#endif // STORAGE_H

/*
Save template:

Players Data:
for each player
name, age, color, score, is_passed
cards played
cards in hand

Warsign
peacesign
season
lands
passCounter
lastPlayerPassed
*/