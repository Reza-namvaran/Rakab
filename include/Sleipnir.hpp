#ifndef SLEIPNIR_H
#define SLEIPNIR_H

#include "WarSign.hpp"
#include "Special.hpp"

class Sleipnir : public Special {
  public:
    Sleipnir(const std::string &p_name);

    virtual void use(std::shared_ptr<Player> p_player, IO_Interface& terminal_handler) override;

    void use(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> owner, unsigned int &passCounter);
};

#endif // SLEIPNIR_H
