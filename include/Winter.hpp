#ifndef WINTER_H
#define WINTER_H

#include "Special.hpp"
#include "Soldier.hpp"

class Winter : public Special
{
public:
    Winter(const std::string &p_name);

    virtual void use(Player &player, IO_Interface &terminal_handler) override;

    void use(std::vector<Player *> &players, IO_Interface &terminal_handler);
};

#endif // WINTER_H