#include "GameGuide.hpp"
/// TODO: Add to CMakelists

GameGuide::GameGuide() {}

GameGuide::~GameGuide() {}

void GameGuide::getCardInfo(const std::string& card_name){
  this->terminal_handler.clearScreen();
  this->terminal_handler.print(this->cards_description[card_name]);
  this->terminal_handler.print("press any key to continue");
  this->terminal_handler.onClickInput();
}

std::unordered_map<std::string, std::string> GameGuide::getDescriptions() const { return this->cards_description; }