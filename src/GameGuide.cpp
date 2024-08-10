#include "GameGuide.hpp"
/// TODO: Add to CMakelists

GameGuide::GameGuide() : state(5) {
    canterbury_font = LoadFont("../assets/fonts/Canterbury.ttf");
    
    // Load images
    images = {
        LoadTexture("../assets/pics/condottiere_rules-1.png"),
        LoadTexture("../assets/pics/condottiere_rules-2.png"),
        LoadTexture("../assets/pics/condottiere_rules-3.png"),
        LoadTexture("../assets/pics/condottiere_rules-4.png"),
        LoadTexture("../assets/pics/condottiere_rules-5.png"),
        LoadTexture("../assets/pics/condottiere_rules-6.png"),
        LoadTexture("../assets/pics/condottiere_rules-7.png"),
        LoadTexture("../assets/pics/condottiere_rules-8.png"),

    };

    // Initially displaying the first image
    currentImageIndex = 0;
    currentImage = images[currentImageIndex];

    // Button dimensions and position
    next_button = {{ 1000, 400, 120, 50 }, "Next", false};
    previous_button = {{ 250, 400, 120, 50}, "Previous", false};
    back_button = {{ 20, 20, 100, 50 }, "Back", false};
}

void GameGuide::getGuidline() {
    Vector2 mousePoint = GetMousePosition();
    this->state = 5;

    if (CheckCollisionPointRec(mousePoint, next_button.rect)) {
        // Toggle to the next image (cycle through images)
        next_button.hover = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentImageIndex = (currentImageIndex + 1) % 8;
            currentImage = images[currentImageIndex];
        }
    }
    
    else if (CheckCollisionPointRec(mousePoint, previous_button.rect)) {
        previous_button.hover = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentImageIndex = (currentImageIndex - 1 + 8) % 8;
            currentImage = images[currentImageIndex];
        }
    }

    else if (CheckCollisionPointRec(mousePoint, back_button.rect)) {
        back_button.hover = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            this->state = 4;
        }
    }
    else
    {
        previous_button.hover = false;
        next_button.hover = false;
        back_button.hover = false;
    }
}

int GameGuide::getStatus() const { return this->state; }

void GameGuide::setStatus(int state) { this->state = state;}

void GameGuide::render() {
    DrawTexture(currentImage, 1400 / 2 - currentImage.width / 2, 900 / 2 - currentImage.height / 2, WHITE);
        
    // Draw the buttons
    DrawTextEx(canterbury_font, next_button.text, (Vector2){next_button.rect.x + 10, next_button.rect.y + 10},
                canterbury_font.baseSize, 1, next_button.hover ? RED : LIGHTGRAY);
    DrawTextEx(canterbury_font, previous_button.text, (Vector2){previous_button.rect.x + 10, previous_button.rect.y + 10},
                canterbury_font.baseSize, 1, previous_button.hover ? RED : LIGHTGRAY);
    DrawTextEx(canterbury_font, back_button.text, (Vector2){back_button.rect.x + 10, back_button.rect.y + 10},
                canterbury_font.baseSize, 1, back_button.hover ? RED : LIGHTGRAY);
}

GameGuide::~GameGuide() {
    for (int i = 0; i < 8; i++) {
        UnloadTexture(images[i]);
    }
}
