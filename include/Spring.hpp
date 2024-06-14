#ifndef SPRING_H
#define SPRING_H

#include "Special.hpp"
#include "Soldier.hpp"

class Spring : public Special
{
public:
    Spring(const std::string &p_name);

    virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) override;

    void use(std::vector<std::shared_ptr<Player>> &players, IO_Interface &terminal_handler);
};

#endif // SPRING_H