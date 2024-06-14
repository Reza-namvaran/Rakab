#ifndef MATCH_H
#define MATCH_H

#include "Player.hpp"
#include "Card.hpp"
#include "CardDeck.hpp"
#include "IO_Interface.hpp"
#include "Land.hpp"
#include "WarSign.hpp"
#include "PlayerSign.hpp"
#include <memory>

class Match
{
private:
    IO_Interface terminal_handler;
    std::vector<std::shared_ptr<Player>> players;
    bool is_match_over = false;
    std::shared_ptr<CardDeck> deck;
    std::shared_ptr<WarSign> warSign;
    std::shared_ptr<Special> season = nullptr;
    std::vector<std::shared_ptr<Land>> lands;
    std::vector<std::vector<std::shared_ptr<Land>>> adjacentList;
    unsigned int passCounter = 0;
    std::shared_ptr<Player> lastPlayerPassed = nullptr;

public:
    Match(std::vector<std::shared_ptr<Player>> p_players);

    ~Match();

    void setSeason(std::shared_ptr<Special> season);

    std::shared_ptr<Special> getSeason() const;

    void dealCard();

    void rechargeDeck();

    void refreshData();

    unsigned int findStarterPlayer() const;

    void playerChoice(std::shared_ptr<Player> player);

    void setWarLand();

    void run();

    void war();

    void calculateScore();

    void stateWinner();

    void winner(std::shared_ptr<Player> winner);
};

#endif // MATCH_H