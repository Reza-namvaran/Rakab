#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <memory>

#include "State.hpp"
#include "Intro.hpp"
#include "MainMenu.hpp"
#include "PlayerSetup.hpp"
#include "LoadMenu.hpp"
#include "Match.hpp"

class StateManager {
  private:
    std::shared_ptr<State> current_state;
    std::shared_ptr<PlayerSetup> player_info;
    std::shared_ptr<LoadMenu> load_menu;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Match> loaded_match;

  public:
    StateManager();
    ~StateManager() = default;

    void init();

    void Process();
    void Update();
    void Render();

    void EventListener();
};

#endif // STATEMANAGER_H
