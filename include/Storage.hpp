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

class Storage {
  public:
    Storage();

    ~Storage() = default;

    void savePlayerInfo(std::shared_ptr<Player> p_player,const std::string& path) const;

    void saveMatchInfo(std::shared_ptr<Match> match, const std::string& path) const;

    void saveNewGame(std::vector<std::shared_ptr<Player>> p_player);

    std::string generateFileName() const;

    void load();  
  
  private:
    static const int MAX_SAVES = 5;
    const std::string SAVE_FOLDER = "data/";
    const std::string SAVE_FILE_PREFIX = "rakab_";
    const std::string SAVE_FILE_EXTENSION = ".txt";
    std::deque<std::string> save_files;
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