#include "System.hpp"

System::System()
{
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));
    this->terminal_handler.clearScreen();

    // initialize GUI requirements
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

void System::run()
{
    // Game loop
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
