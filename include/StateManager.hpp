#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <memory>

#include "State.hpp"
#include "Intro.hpp"
#include "MainMenu.hpp"
#include "PlayerSetup.hpp"
#include "Match.hpp"

class StateManager {
  private:
    std::shared_ptr<State> current_state;
    std::shared_ptr<PlayerSetup> player_info;
    std::vector<std::shared_ptr<Player>> players;

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
