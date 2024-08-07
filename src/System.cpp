#include "System.hpp"

System::System() : database(std::make_shared<Storage>())
{
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));
    this->terminal_handler.clearScreen();
    // this->mainMenu();
    InitWindow(1400, 900, "Rakab");

    InitAudioDevice();

    Image fav_icon = LoadImage("../assets/pics/fav_icon.png");
    SetWindowIcon(fav_icon);
    UnloadImage(fav_icon);

    SetTargetFPS(60);

    this->state_manager.init();

    this->run();
}

System::~System() {
    CloseAudioDevice();

    CloseWindow();
}

// void System::createNewMatch()
// {
//     // auto new_match = std::make_shared<Match>(this->initialize());
//     this->match_list[match_list.size() + 1] = new_match;
// }

// void System::runMatch(int match_id)
// {
//     this->match_list.at(match_id)->run();
// }

void System::run()
{
    while(!WindowShouldClose())
    {
        this->state_manager.Process();
        this->state_manager.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        this->state_manager.Render();
        EndDrawing();

        this->state_manager.EventListener();
    }
}

// void System::mainMenu()
// {
//     this->terminal_handler.print("Press n for starting a new match or e to exit or choose a saved game(1 to 5)");
//     int counter = 1;
//     for (const std::string &fileName : this->database->getFilesNames())
//     {
//         this->terminal_handler.print(std::to_string(counter) + "." + fileName);
//         counter++;
//         std::shared_ptr<Match> new_match = std::make_shared<Match>(this->database);
//         this->database->loadMatch(new_match, fileName);
//         this->match_list[this->match_list.size() + 1] = new_match;
//     }

//     char c;
//     c = getch();

//     while (1)
//     {
//         switch (c)
//         {
//         case 'n':
//             this->terminal_handler.clearScreen();
//             this->createNewMatch();
//             runMatch(this->match_list.size());
//             break;
//         case 'e':
//             return;
//         default:
//             runMatch(c - '0');
//         }
//     }
// }