#include "StateManager.hpp"

StateManager::StateManager() {}

void StateManager::init() {
    this->current_state = std::make_shared<Intro>();
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

    switch (next_state_id) {
        case 0:
            // Keep Listening
            break;

        case 2:
            // MainMenu
            std::clog << "[LOG]: Switch to MainMenu." << "\n";
            current_state = std::make_shared<MainMenu>();
            break;

        case 3:
            // Player Setup page
            std::clog << "[LOG]: Switch to Player Setup Page." << "\n";
            current_state = std::make_shared<PlayerSetup>();
            break;
        
        case 4:
            // LoadGame Menu
            std::clog << "[LOG]: Switch to Load Menu Page." << "\n";
            current_state = std::make_shared<LoadMenu>();
            break;

        case 5:
            // Going to a new match
            std::clog << "[LOG]: Switch to Match" << "\n";
            player_info = std::dynamic_pointer_cast<PlayerSetup>(current_state);
            players = player_info->getData();
            current_state = std::make_shared<Match>(players);
            break;

        case 6:
            // Load a saved match
            std::clog << "[LOG]: Switch to Loaded Match" << "\n";
            load_menu = std::dynamic_pointer_cast<LoadMenu>(current_state);
            loaded_match = load_menu->getMatch();
            
            current_state = loaded_match;

            break;
        case -1:
            CloseWindow();
            break;

        default:
            std::clog << "[Error]: Changing state failed!" << "\n";
            break;
    }
}