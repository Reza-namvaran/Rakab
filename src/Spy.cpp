#include "Spy.hpp"

Spy::Spy(const std::string& p_name) : Special(p_name,"../assets/pics/spy.png") {}

void Spy::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {
  player->setPlayerScore(player->getPlayerScore() + 1);
}