#include "GameGuide.hpp"
/// TODO: Add to CMakelists

GameGuide::GameGuide() {
  this->readGameRules();
  this->readCardInfo();
  this->readValidCommands();
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
  std::ifstream input("../data/gamerules.txt");

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
  std::ifstream input("../data/card_info.txt");

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

void GameGuide::readValidCommands() {
  std::ifstream input("../data/valid_commands.txt");

  std::string line;
  while(std::getline(input, line))
  {
    this->valid_commands.emplace(line);
  }

  input.close();
}

int GameGuide::leveshteinDistance(const std::string& str1, const std::string str2, const int& str1_len,const int& str2_len) const{
  if(str1_len == 0)
  {
    return str2_len;
  }

  if(str2_len == 0)
  {
    return str1_len;
  }

  if(str1[str1_len - 1] == str2[str2_len - 1])
	  return leveshteinDistance(str1, str2, str1_len - 1, str2_len - 1); 

	return 1 + std::min(leveshteinDistance(str1, str2, str1_len, str2_len - 1), std::min(leveshteinDistance(str1, str2, str1_len - 1,str2_len),leveshteinDistance(str1, str2, str1_len - 1,str2_len - 1)));
}

std::string GameGuide::suggestion(std::string& str) const{
    int min_dis = str.length();
    std::string key_idx;

    if(this->valid_commands.find(str) != this->valid_commands.end())
        return str;

    for(const auto& key : this->valid_commands)
    {
        int distance = this->leveshteinDistance(str, key, str.length(), key.length());
        if(distance >= str.length())
          continue;
        if(distance < min_dis)
        {
            min_dis = distance;
            key_idx = key;
        }
    }

    return key_idx;
}