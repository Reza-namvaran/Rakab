#ifndef MIRAGE_H
#define MIRAGE_H

#include <random>

#include "Special.hpp"
#include "Soldier.hpp"

class Mirage : public Special {
  public:
    Mirage(const std::string& p_name);

    virtual void use(std::shared_ptr<Player> p_player, IO_Interface& terminal_handler) override; 
};

#endif // MIRAGE_H
