#ifndef SPRING_H
#define SPRING_H

#include "Special.hpp"
#include "Soldier.hpp"

class Spring : public Special
{
public:
    Spring(const std::string &p_name);

    virtual void use(Player &player, IO_Interface &terminal_handler) override;

    void use(std::unordered_set<Player *> &players, IO_Interface &terminal_handler);
};

#endif // SPRING_H