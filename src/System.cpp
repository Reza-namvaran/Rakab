#include "System.hpp"

System::System() {
  /// NOTE: Seed the random number generator with the current time
  srand(static_cast<unsigned int>(time(nullptr)));
  this->initialize();
}

System::~System() {}

std::vector<Player> System::initialize() {
  int player_count = 0;

  this->terminal_handler.print("Please enter the number of players: ");
  this->terminal_handler.input(player_count);

  std::vector<Player> players;

  // Creating Players based on inputs
  for(int idx = 0; idx < player_count; ++idx)
  {
    std::string name;
    unsigned int age;

    this->terminal_handler.print("Please enter player" + std::to_string(idx + 1) + " 's name: ");
    this->terminal_handler.input(name);
    this->terminal_handler.input(age);

    Player new_player(name, age);

    players.emplace_back(new_player);
  }

  return players;
}

// void System::selectMatch(int match_id){
  /// TODO: Implement this method
// }

void System::runMatch(int match_id){
  
}