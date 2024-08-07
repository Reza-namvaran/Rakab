#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <memory>

#include "State.hpp"
#include "Intro.hpp"
#include "MainMenu.hpp"
#include "PlayerSetup.hpp"

class StateManager {
  private:
    std::unique_ptr<State> current_state;

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
