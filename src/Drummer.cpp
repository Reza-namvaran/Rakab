#include "Drummer.hpp"

Drummer::Drummer(const std::string p_name) : Special("Drummer","../assets/pics/drummer.png") {}

void Drummer::use(std::shared_ptr<Player> player, IO_Interface &terminal_handler)
{
    terminal_handler.print("All of " + player->getPlayerName() + "'s soldiers' scores will be doubled.\n");
    player->setPlayerScore(player->getPlayerScore() * 1.5);
}