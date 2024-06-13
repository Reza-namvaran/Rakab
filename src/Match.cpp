#include "Match.hpp"
#include "CardDeck.cpp"

Match::Match(std::vector<Player> p_players) : players(p_players) {}

Match::~Match() {}

int Match::findRoundStarter(bool first_round){
    if(first_round)
    {
        unsigned int min_age = players[0].getPlayerAge();
        int first_player = 0;
        for(int idx = 0; idx < players.size(); ++idx)
        {
            if(players[idx].getPlayerAge() < min_age)
            {
                min_age = players[idx].getPlayerAge();
                first_player = idx;
            }
        }

        this->terminal_handler.print(players[first_player].getPlayerName() + " shall start the game");
        return first_player;
    }

    return -1;
}

void Match::run() {
    CardDeck test;
    int first_player = this->findRoundStarter(true);
    for(const auto& card : test.getDeck())
        std::cout << card->getCardType() << " " << card->getCardName() << "\n";
    
}