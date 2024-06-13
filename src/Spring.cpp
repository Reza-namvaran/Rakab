#include "Spring.hpp"

Spring::Spring(const std::string& p_name) : Special(p_name) {}

void Spring::use(Player &player, IO_Interface &terminal_handler)
{
    terminal_handler.print("Spring has been played! \n");
    player.setPlayerScore(player.getPlayerScore() + 3);
    /// TODO: do something for the case when spring comes after winter
}
