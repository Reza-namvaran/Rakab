#include "System.hpp"

System::System()
{
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));
    this->terminal_handler.clearScreen();
    this->mainMenu();
}

System::~System() {}

std::vector<std::shared_ptr<Player>> System::initialize()
{
    int player_count = 0;
    while (true)
    {
        this->terminal_handler.print("Please enter the number of players: ");
        std::string input_str;
        this->terminal_handler.input(input_str);

        try
        {
            player_count = std::stoi(input_str);
            if (player_count <= 0)
            {
                throw std::invalid_argument("Number of players must be a positive integer.");
            }
            else if (player_count < 3 || player_count > 6)
            {
                throw std::invalid_argument("Number of players must be between 3 to 6");
            }
            break;
        }
        catch (const std::invalid_argument &)
        {
            this->terminal_handler.print("Invalid input. Please enter a positive integer between 3 to 6");
        }
        catch (const std::out_of_range &)
        {
            this->terminal_handler.print("Input is out of range. Please enter a smaller number.");
        }
    }

    std::vector<std::shared_ptr<Player>> players;
    this->terminal_handler.clearScreen();

    std::unordered_set<std::string> player_signs{"Blue", "Green", "Red", "Yellow", "Gray", "Purple"};

    // Creating Players based on inputs
    for (int idx = 0; idx < player_count; ++idx)
    {
        std::string name;
        unsigned int age;

        this->terminal_handler.print("Please enter player" + std::to_string(idx + 1) + "'s name: ");
        this->terminal_handler.input(name);

        while (true)
        {
            this->terminal_handler.print("Please enter player" + std::to_string(idx + 1) + "'s age: ");
            std::string input_str;
            this->terminal_handler.input(input_str);

            try
            {
                int temp_age = std::stoi(input_str);
                if (temp_age < 0)
                {
                    throw std::invalid_argument("Age must be a non-negative integer.");
                }
                age = static_cast<unsigned int>(temp_age);
                break;
            }
            catch (const std::invalid_argument &)
            {
                this->terminal_handler.print("Invalid input. Please enter a non-negative integer.");
            }
            catch (const std::out_of_range &)
            {
                this->terminal_handler.print("Input is out of range. Please enter a smaller number.");
            }
        }

        for (const auto &color : player_signs)
        {
            this->terminal_handler.print(color, false);
        }

        std::string player_color;
        while (true)
        {
            this->terminal_handler.print("\nPlayer" + std::to_string(idx + 1) + ", Please pick a sign to play: ");
            this->terminal_handler.input(player_color);

            if (player_signs.find(player_color) != player_signs.end())
            {
                // The color sign is available
                break;
            }
            else
            {
                this->terminal_handler.print("\nInvalid color sign. Please choose from the available signs.");
            }
        }

        auto new_player = std::make_shared<Player>(name, age, player_color);
        new_player->getSign()->setOwner(new_player);
        player_signs.erase(player_color);

        players.emplace_back(new_player);
        this->terminal_handler.clearScreen();
    }

    return players;
}

void System::createNewMatch()
{
    auto new_match = std::make_shared<Match>(this->initialize());
    this->match_list.insert({match_list.size() + 1, new_match});
}

void System::runMatch(int match_id)
{
    this->match_list.at(match_id)->run();
}

void System::mainMenu()
{
    this->terminal_handler.print("Press n for starting a new match or l to load a match or e to exit");
    char c;
    std::cin >> c;
    std::cin.ignore();
    int id = 1;

    while(1)
    {
        switch(c){
            case 'n':
                    this->terminal_handler.clearScreen();
                    this->createNewMatch();
                    id = this->match_list.size();
                    runMatch(id);
                    
                    if(this->match_list.at(id)->getSaveStatus())
                    {
                        this->database.saveNewGame(this->match_list.at(id));
                        std::clog << "Save: successful" << std::endl;
                    }
                    std::cin >> c;
                    std::cin.ignore();
                    break;
            
            case 'l':
                this->terminal_handler.print("Please select a match: ");
                for(const auto& match : this->match_list)
                    this->terminal_handler.print(match.first);
                
                int id;
                std::cin >> id;
                std::cin.ignore();

                runMatch(id);
                break;

            case 'e':
                return;

            default:
                this->terminal_handler.print("Enter a valid option, n or l or e");
        }
    }
}