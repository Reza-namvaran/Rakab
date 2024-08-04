#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <filesystem>
#include <deque>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

#include "Match.hpp"

class Match;

class Storage
{
public:
  Storage();

  ~Storage() = default;

  std::deque<std::string> getFilesNames() const;

  void saveNewGame(std::shared_ptr<Match> match, std::shared_ptr<Player> playerTurn);

  void loadAllMatch() const;

private:
  static std::deque<std::string> save_files;
  /// NOTE: using deque as a ring buffer

  /// ------------------------ private function members ---------------------------
  void savePlayerInfo(std::shared_ptr<Player> p_player, const std::string &path) const;
  void saveMatchInfo(std::shared_ptr<Match> match, const std::string &path, std::shared_ptr<Player> playerTurn) const;
  std::string generateFileName() const;
  std::vector<std::shared_ptr<Card>> splitAndCapture(const std::string &str) const;
  void loadMatch(std::shared_ptr<Match> match, const std::string &path) const;
  /// -----------------------------------------------------------------------------
};

#endif // STORAGE_H
