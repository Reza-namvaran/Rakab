#include "Heroine.hpp"

Heroine::Heroine(const std::string& p_name) : Special(p_name,"../assets/pics/heroine.png") {}

void Heroine::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler) {
  player->setPlayerScore(player->getPlayerScore() + 10);
}