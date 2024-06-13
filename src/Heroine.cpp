#include "Heroine.hpp"

Heroine::Heroine(const std::string& p_name) : Special(p_name) {}

void Heroine::use(Player &player, IO_Interface &terminal_handler) {
  player.setPlayerScore(player.getPlayerScore() + 10);
}