#ifndef GAMEGUIDE_H
#define GAMEGUIDE_H

#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>

#include "IO_Interface.hpp"

class GameGuide {
  private:
    IO_Interface terminal_handler;
    std::string game_rules;
    std::unordered_map<std::string, std::string> cards_description;

    std::unordered_set<std::string> valid_commands;

  public:
    GameGuide();

    ~GameGuide();

    void readGameRules();

    void readCardInfo();

    void readValidCommands();

    std::unordered_map<std::string, std::string> getDescriptions() const;

    void getCardInfo(const std::string& card_name);

    void getGameRules();

    int leveshteinDistance(const std::string& str1, const std::string str2, const int& str1_len,const int& str2_len) const;

    std::string suggestion(std::string& str) const;
};

#endif // GAMEGUIDE_H
