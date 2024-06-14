#ifndef WINTER_HPP
#define WINTER_HPP

#include <memory>
#include <vector>
#include <string>

#include "Special.hpp"
#include "Soldier.hpp"

class Winter : public Special {
public:
    Winter(const std::string &p_name);

    virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) override;
    void use(std::vector<std::shared_ptr<Player>> &players, IO_Interface &terminal_handler);
};

#endif // WINTER_HPP