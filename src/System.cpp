#include "System.hpp"

System::System() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));
    this->terminal_handler.clearScreen();
    this->createNewMatch();
    runMatch(1);
}

System::~System() {}

std::vector<std::shared_ptr<Player>> System::initialize() {
    int player_count = 0;
    this->terminal_handler.print("Please enter the number of players: ");
    this->terminal_handler.input(player_count);

    std::vector<std::shared_ptr<Player>> players;
    this->terminal_handler.clearScreen();
        
    std::unordered_set<std::string> player_signs {"Blue", "Green", "Red", "Yellow", "Gray", "Purple"};
    
    // Creating Players based on inputs
    for (int idx = 0; idx < player_count; ++idx) {
        std::string name;
        unsigned int age;
        std::string colors = "", player_color;

        this->terminal_handler.print("Please enter player" + std::to_string(idx + 1) + "'s name: ");
        this->terminal_handler.input(name);
        this->terminal_handler.print("Please enter player" + std::to_string(idx + 1) + "'s age: ");
        this->terminal_handler.input(age);


        for(auto& sign : player_signs)
            colors += sign + " ";
        
        this->terminal_handler.print(colors);

        this->terminal_handler.print("Player" + std::to_string(idx + 1) + ", Please pick a sign to play: ");
        this->terminal_handler.input(player_color);

        auto new_player = std::make_shared<Player>(name, age, player_color);
        player_signs.erase(player_color);

        players.emplace_back(new_player);
        this->terminal_handler.clearScreen();
    }

    


    return players;
}

void System::createNewMatch() {
    auto new_match = std::make_shared<Match>(this->initialize());
    matches.emplace_back(new_match);
}

void System::runMatch(int match_id) {
    this->matches[match_id - 1]->run();
}
