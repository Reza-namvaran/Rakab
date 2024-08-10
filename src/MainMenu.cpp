#include "MainMenu.hpp"
// #include <iostream>
MainMenu::MainMenu() : NUM_BACKGROUNDS(3), CHANGE_INTERVAL(5.0f) {
    status = 0;
    main_menu_music = LoadMusicStream("../assets/audio/soundtrack.wav");
    button_sound = LoadSound("../assets/audio/button.wav");
    canterbury_font = LoadFont("../assets/fonts/Canterbury.ttf");
    menu_bar = LoadTexture("../assets/pics/menu_bar.png");

    backgrounds[0] = LoadTexture("../assets/pics/knight.png");
    backgrounds[1] = LoadTexture("../assets/pics/castle.png");
    backgrounds[2] = LoadTexture("../assets/pics/fire.png");

    buttons[0] = (Button){(Rectangle){185, 300, 120, 50}, "Start", false};
    buttons[1] = (Button){(Rectangle){145, 370, 120, 50}, "Load Game", false};
    buttons[2] = (Button){(Rectangle){195, 440, 120, 50}, "Exit", false};

    PlayMusicStream(main_menu_music);
}

MainMenu::~MainMenu() {
    StopMusicStream(main_menu_music);
    // Clean up resources
    for (int i = 0; i < NUM_BACKGROUNDS; i++) {
        UnloadTexture(backgrounds[i]);
    }
    UnloadTexture(menu_bar);
    UnloadMusicStream(main_menu_music);
    UnloadSound(button_sound);
    UnloadFont(canterbury_font);
}

void MainMenu::Process() {
    Vector2 mousePoint = GetMousePosition();
    for (int i = 0; i < 3; i++) {
        if (CheckCollisionPointRec(mousePoint, buttons[i].rect)) {
            buttons[i].hover = true;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selected_button = i;
                PlaySound(button_sound);
                if (i == 2) {
                    // Exit
                    this->status = -1;
                }
                else if (i == 1) {
                    this->status = 4;
                }
                else if(i == 0) {
                    // Start New Game
                    this->status = 3;
                }
            }
        } else {
            buttons[i].hover = false;
        }
    }
}

void MainMenu::Update()  {
    float deltaTime = GetFrameTime();
    changeTimer += deltaTime;
    UpdateMusicStream(main_menu_music);

    if (changeTimer >= CHANGE_INTERVAL) {
        current_background = (current_background + 1) % NUM_BACKGROUNDS;
        next_background = (current_background + 1) % NUM_BACKGROUNDS;
        changeTimer = 0.0f;
        fadeAlpha = 0.0f;
    }

    if (fadeAlpha < 1.0f) {
        fadeAlpha += deltaTime / 2;
        if (fadeAlpha > 1.0f) fadeAlpha = 1.0f;
    }
}

void MainMenu::Render()  {
    Rectangle sourceRec = { 0.0f, 0.0f, (float)backgrounds[current_background].width, (float)backgrounds[current_background].height };
    Rectangle destRec = { 0.0f, 0.0f, (float)1400, (float)900 };

    DrawTexturePro(backgrounds[current_background], sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
    DrawTexturePro(backgrounds[next_background], sourceRec, destRec, (Vector2){0, 0}, 0.0f, Fade(WHITE, fadeAlpha));

    DrawTexture(menu_bar, 100, 0, WHITE); 

    for (int i = 0; i < 3; i++) {
        Color textColor = buttons[i].hover ? RED : LIGHTGRAY;
        DrawTextEx(canterbury_font, buttons[i].text, (Vector2){buttons[i].rect.x + 10, buttons[i].rect.y + 10},
                    canterbury_font.baseSize, 1, textColor);
    }
}
