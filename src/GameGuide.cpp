#include "GameGuide.hpp"
/// TODO: Add to CMakelists

GameGuide::GameGuide() {
  this->readGameRules();
  this->readCardInfo();
}

GameGuide::~GameGuide() {}

void GameGuide::getCardInfo(const std::string& card_name){
  this->terminal_handler.clearScreen();
  this->terminal_handler.print(this->cards_description[card_name]);
  this->terminal_handler.print("press any key to continue");
  this->terminal_handler.onClickInput();
}

std::unordered_map<std::string, std::string> GameGuide::getDescriptions() const { return this->cards_description; }

void GameGuide::getGameRules() {  
  this->terminal_handler.clearScreen();
  this->terminal_handler.print(this->game_rules);
  this->terminal_handler.print("press any key to continue");
  this->terminal_handler.onClickInput();  
}

void GameGuide::readGameRules() {
  std::ifstream input("../data/gamerules.bin", std::ios::binary);

  if(!input.is_open())
  {
    this->terminal_handler.print("Error opening the file!");
    return;
  }
  std::string line;
  
  while(std::getline(input, line))
  {
    this->game_rules += line + "\n";
  }

  input.close();
}

void GameGuide::readCardInfo() {
  std::ifstream input("../data/card_info.bin", std::ios::binary);

  if(!input.is_open())
  {
    this->terminal_handler.print("Error opening the file!");
    return;
  }

  std::string line;

  while(std::getline(input, line))
  {
    auto it = line.find(' ');    
    if(it != std::string::npos)
    {
      std::string key = line.substr(0, it);
      std::string value = line.substr(it + 1);
      this->cards_description[key] = value;
    }
  }

  input.close();
}
