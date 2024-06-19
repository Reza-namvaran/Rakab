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

    std::unordered_set<std::string> valid_commands = {
      {"Winter"}, {"Spring"}, {"Heroine"}, {"One"}, {"Two"}, {"Three"}, {"Four"}, {"Five"}, {"Six"}, {"Ten"}, {"Drummer"}, {"Scarecrow"}, {"help"}, {"pass"}, {"help Winter"}, {"help Spring"}
    };

  public:
    GameGuide();

    ~GameGuide();

    /// TODO: is_valid_input()

    /// TODO: Implement getGameRules()

    void readGameRules();

    void readCardInfo();

    std::unordered_map<std::string, std::string> getDescriptions() const;

    void getCardInfo(const std::string& card_name);

    void getGameRules();

    std::unordered_set<std::string> getCommands() const;
};

#endif // GAMEGUIDE_H
