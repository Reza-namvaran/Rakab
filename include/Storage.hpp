#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <filesystem>
#include <deque> 
/// NOTE: deque to use ring buffer 

#include "Match.hpp"

class Storage {
  public:
    Storage();

    ~Storage() = default;

    void savePlayerInfo(const Player& p_player) const;

    void saveNewGame();

    void load();  
  
  private:
    static const int MAX_SAVES = 5;
};

#endif // STORAGE_H

/*
Save template:

Players Data:
for each player
name, age, color, score, is_passed
cards played
cards in hand

Warsign
peacesign
season
lands
passCounter
lastPlayerPassed
*/