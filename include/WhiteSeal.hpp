#ifndef WHITESEAL_H
#define WHITESEAL_H

#include <algorithm>

#include "Special.hpp"

class WhiteSeal : public Special {
  public:
    WhiteSeal(const std::string p_name);

    virtual void use(std::shared_ptr<Player> p_player, IO_Interface& terminal_handler) override;

    void use(std::vector<std::shared_ptr<Player>> players);
};


#endif // WHITESEAL_H
