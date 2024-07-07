#ifndef BISHOP_H
#define BISHOP_H

#include "Special.hpp"
#include "Soldier.hpp"

class Bishop : public Special {
  public:
    Bishop(const std::string& p_name);

    virtual void use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) override;

    void use(std::vector<std::shared_ptr<Player>> &players);
};

#endif