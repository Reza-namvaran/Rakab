#ifndef MATCH_H
#define MATCH_H

#include <memory>
#include <unordered_set>
#include <algorithm>

#include "Player.hpp"
#include "Card.hpp"
#include "CardDeck.hpp"
#include "IO_Interface.hpp"
#include "Land.hpp"
#include "WarSign.hpp"
#include "PlayerSign.hpp"
#include "GameGuide.hpp"
#include "PeaceSign.hpp"
#include "Storage.hpp"
#include "State.hpp"

class Storage;

struct land_btn {
    Rectangle rect;
    std::string name;
    bool active;
};

class Match : public State
{
private:
    IO_Interface terminal_handler;
    std::vector<std::shared_ptr<Player>> players;
    bool is_match_over = false;
    std::shared_ptr<CardDeck> deck;
    std::shared_ptr<WarSign> warSign;
    std::shared_ptr<PeaceSign> peace_sign;
    std::shared_ptr<Special> season = nullptr;
    std::vector<std::shared_ptr<Land>> lands;   // All lands in game
    std::vector<std::vector<std::shared_ptr<Land>>> adjacentList; // Adjacent Matrix
    unsigned int passCounter = 0;
    std::shared_ptr<Player> lastPlayerPassed = nullptr;
    std::shared_ptr<Player> lastPlayerBishoped = nullptr;
    GameGuide guide;
    std::shared_ptr<Storage> database;
    int loadPlayerTurn;
    int PlayerTurn;
    
    int match_state;
    Texture2D Map;
    Vector2 mousePosition;
    Texture2D war_background;
    Texture2D winter_background;
    Texture2D spring_background;


public:
    Match( std::shared_ptr<Storage> database);
    Match(std::vector<std::shared_ptr<Player>> p_players);

    ~Match();

    friend class Storage;

    void displayStatus();

    void setSeason(std::shared_ptr<Special> season);

    std::shared_ptr<Special> getSeason() const;

    void checkSaveStatus(std::shared_ptr<Player> playerTurn);

    void resetMatchstatus();

    void dealCardsToPlayers();

    void rechargeDeck();

    void refreshData();

    unsigned int findStarterPlayer() const;

    void playerChoice(std::shared_ptr<Player> player);

    void setWarSignOwner(std::shared_ptr<Player> p_player = nullptr);

    void setPeaceSignOwner();

    void setWarLand();

    void setPeaceLand();

    void run();

    void war();

    void calculateScore();

    void stateWinner();

    void gameWinner(std::shared_ptr<Player> winner);

    virtual void Process() override;

    virtual void Update() override;

    virtual void Render() override;
};

#endif // MATCH_H