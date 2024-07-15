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

class System {
private:
    IO_Interface terminal_handler;
    // std::vector<std::shared_ptr<Match>> matches;
    std::unordered_map<int, std::shared_ptr<Match>> match_list;
    Storage database;

public:
    System();
    ~System();

    void mainMenu();
    void createNewMatch();
    std::vector<std::shared_ptr<Player>> initialize();
    void runMatch(int match_id);
};

#endif // SYSTEM_H