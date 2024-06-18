#ifndef GAMEGUIDE_H
#define GAMEGUIDE_H

#include <unordered_map>
#include <unordered_set>

#include "IO_Interface.hpp"

class GameGuide {
  private:
    IO_Interface terminal_handler;
    std::string game_rules = "This is a prototype";
    std::unordered_map<std::string, std::string> cards_description = {
      {"One", "Increases player's score by one"},
      {"Two", "Increases player's score by two"},
      {"Three", "Increases player's score by three"},
      {"Four", "Increases player's score by four"},
      {"Five", "Increases player's score by five"},
      {"Six", "Increases player's score by six"},
      {"Seven", "Increases player's score by seven"},
      {"Herione", "For each Heroine in your row, add 10 to your strength.\nThe Heroine is not a soldier,\nso its value is not affected by the Bishop, Winter, the Drummer, or Spring, but its added strength is applied last to avoid any confusion"},
      {"Spring", "While Spring is in play, check which soldier has the highest value among all player rows.\nAdd “3” to the value of all copies of that card in all player rows.\nNote that the soldier affected by Spring can change during the battle\nOnly winter can chanfe spring"},
      {"Winter","While Winter is in play, the value of each soldier in all player rows is 1.\nOnly spring can change the winter"},
      {"Scarecrow", "When you play a Scarecrow, take one of the soldiers from your row back into your hand (if possib0le).\nThe scarecrow cannot be used to take back special cards."},
      {"Drummer", "While you have a Drummer in your row, double the value of each mercenary in your row.\nYou can play additional Drummers, but they have no effect."},
    };

    std::unordered_set<std::string> valid_commands = {
      {"Winter"}, {"Spring"}, {"Heroine"}, {"One"}, {"Two"}, {"Three"}, {"Four"}, {"Five"}, {"Six"}, {"Ten"}, {"Drummer"}, {"Scarecrow"}, {"help"}, {"pass"}, {"help Winter"}, {"help Spring"}
    };

    
  public:
    GameGuide();

    ~GameGuide();

    /// TODO: is_valid_input()

    /// TODO: Implement getGameRules()

    std::unordered_map<std::string, std::string> getDescriptions() const;

    void getCardInfo(const std::string& card_name);

    std::unordered_set<std::string> getCommands() const;
};

#endif // GAMEGUIDE_H