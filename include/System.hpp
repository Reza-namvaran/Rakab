#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <ctime>
#include <memory>

#include "IO_Interface.hpp"
#include "Player.hpp"
#include "Match.hpp"

class System {
private:
    IO_Interface terminal_handler;
    std::vector<std::shared_ptr<Match>> matches;

public:
    System();
    ~System();

    void createNewMatch();
    std::vector<std::shared_ptr<Player>> initialize();
    void selectMatch(int match_id);
    void runMatch(int match_id);
};

#endif // SYSTEM_H