#include "MainMenu.hpp"

MainMenu::MainMenu() : NUM_BACKGROUNDS(3), CHANGE_INTERVAL(5.0f), wants_to_exit(false) {

    main_menu_music = LoadMusicStream("../assets/audio/soundtrack.wav");
    button_sound = LoadSound("../assets/audio/button.wav");
    canterbury_font = LoadFont("../assets/fonts/Canterbury.ttf");

    backgrounds[0] = LoadTexture("../assets/pics/knight.png");
    backgrounds[1] = LoadTexture("../assets/pics/castle.png");
    backgrounds[2] = LoadTexture("../assets/pics/n.png");

    buttons[0] = (Button){(Rectangle){50, 150, 120, 50}, "Start", false};
    buttons[1] = (Button){(Rectangle){50, 220, 120, 50}, "Options", false};
    buttons[2] = (Button){(Rectangle){50, 290, 120, 50}, "Exit", false};
}

MainMenu::~MainMenu() {
    // Clean up resources
    for (int i = 0; i < NUM_BACKGROUNDS; i++) {
        UnloadTexture(backgrounds[i]);
    }
    UnloadMusicStream(main_menu_music);
    UnloadSound(button_sound);
    UnloadFont(canterbury_font);
}

void MainMenu::EnterState()  {
    PlayMusicStream(main_menu_music);
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
                    wants_to_exit = true;
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

    for (int i = 0; i < 3; i++) {
        Color textColor = buttons[i].hover ? RED : LIGHTGRAY;
        DrawTextEx(canterbury_font, buttons[i].text, (Vector2){buttons[i].rect.x + 10, buttons[i].rect.y + 10},
                    canterbury_font.baseSize, 1, textColor);
    }

    DrawText("Press P to toggle popup", 10, 10, 20, DARKGRAY);
}

void MainMenu::ExitState() {
    StopMusicStream(main_menu_music);
}