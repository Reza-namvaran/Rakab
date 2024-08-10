#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <ctime>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>

#include "IO_Interface.hpp"
#include "Player.hpp"
#include "Match.hpp"
#include "StateManager.hpp"

class System
{
private:
    IO_Interface terminal_handler;
    StateManager state_manager;

public:
    System();
    ~System();

    // void mainMenu();
    // void createNewMatch();
    // void runMatch(int match_id);
    void run();
};

#endif // SYSTEM_H