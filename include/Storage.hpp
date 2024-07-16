#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <filesystem>
#include <deque> 
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <cassert>

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
    static std::deque<std::string> save_files;

    /// ------------------------ private function members ---------------------------
    void savePlayerInfo(std::shared_ptr<Player> p_player,const std::string& path) const;
    void saveMatchInfo(std::shared_ptr<Match> match, const std::string& path) const;
    std::string generateFileName() const;
    /// -----------------------------------------------------------------------------
};

#endif // STORAGE_H