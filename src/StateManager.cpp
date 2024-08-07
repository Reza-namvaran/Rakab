#include "StateManager.hpp"

StateManager::StateManager() {}

void StateManager::init() {
    this->current_state = std::make_unique<Intro>();
}

void StateManager::Process() {
    this->current_state->Process();
}

void StateManager::Update() {
    this->current_state->Update();
}

void StateManager::Render() {
    this->current_state->Render();
}

void StateManager::EventListener() {
    int next_state_id = current_state->getStatus();

    switch(next_state_id)
    {
        case 0:
            // Keep Listening
            break;

        case 2:
            // MainMenu
            std::clog << "[LOG]: Switch to MainMenu." << "\n";
            this->current_state = std::make_unique<MainMenu>();
            break;

        case 3:
            // Player Setup page
            std::clog << "[LOG]: Switch to Player Setup Page." << "\n";
            this->current_state = std::make_unique<PlayerSetup>();
            break;
        case -1:
            CloseWindow();
        default:
            std::clog << "[Error]: Changing state failed!" << "\n";
            break;
    }

    return;
}



