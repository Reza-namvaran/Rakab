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

  void loadMatch(std::shared_ptr<Match> match, const std::string &path) ;

private:
  static std::deque<std::string> save_files;
  std::shared_ptr<CardDeck> deck;
  /// NOTE: using deque as a ring buffer

  /// ------------------------ private function members ---------------------------
  void savePlayerInfo(std::shared_ptr<Player> p_player, const std::string &path) const;
  void saveMatchInfo(std::shared_ptr<Match> match, const std::string &path, std::shared_ptr<Player> playerTurn) const;
  std::string generateFileName() const;
  std::vector<std::shared_ptr<Card>> splitAndCaptureCards(const std::string &str) ;
  std::vector<std::shared_ptr<Land>> splitAndCaptureLands(const std::string &str, std::shared_ptr<Match> match) ;
  Rectangle splitAndCaptureRecs(const std::string &str);
  /// -----------------------------------------------------------------------------
};

#endif // STORAGE_H
