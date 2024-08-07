#include "Intro.hpp"

Intro::Intro() : logo_position_x(screenWidth/2 - 128), logo_position_y (screenHeight/2 - 128), frames_counter(0), letters_count(0),
top_side_width(0), bottom_side_width(0), left_side_height(0), right_side_height(0), state(0), alpha(1.0f) 
{
    status = 0;
    intro_font = LoadFont("../assets/fonts/pixel.ttf");
}

Intro::~Intro()
{
    UnloadFont(intro_font);
}

void Intro::Process() {}

void Intro::Update()
{
    switch (state)
    {
        case 0:
            frames_counter++;

            if (frames_counter == 120)
            {
                frames_counter = 0;      // Reset counter ---will be used later---
                state = 1;
            }
            break;

        case 1:
            top_side_width += 4;
            left_side_height += 4;

            if (top_side_width == 256) state = 2;
            break;

        case 2:
            bottom_side_width += 4;
            right_side_height += 4;

            if (bottom_side_width == 256) state = 3;
            break;

        case 3:
            frames_counter++;

            if (frames_counter/12)       // Every 12 frames, one more letter!
            {
                letters_count++;
                frames_counter = 0;
            }

            if (letters_count >= 10)     // When all letters have appeared, just fade out everything
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    status = 2;
                }
            }
            break;

        default:
        break;
    }
}

void Intro::Render()
{

    if (state == 0)
    {
        if ((frames_counter/15) % 2) DrawRectangle(logo_position_x, logo_position_y, 16, 16, BLACK);
    }
    else if (state == 1)
    {
        DrawRectangle(logo_position_x, logo_position_y, top_side_width, 16, BLACK);
        DrawRectangle(logo_position_x, logo_position_y, 16, left_side_height, BLACK);
    }
    else if (state == 2)
    {
        DrawRectangle(logo_position_x, logo_position_y, top_side_width, 16, BLACK);
        DrawRectangle(logo_position_x, logo_position_y, 16, left_side_height, BLACK);

        DrawRectangle(logo_position_x + 240, logo_position_y, 16, right_side_height, BLACK);
        DrawRectangle(logo_position_x, logo_position_y + 240, bottom_side_width, 16, BLACK);
    }
    else if (state == 3)
    {
        DrawRectangle(logo_position_x, logo_position_y, top_side_width, 16, Fade(BLACK, alpha));
        DrawRectangle(logo_position_x, logo_position_y + 16, 16, left_side_height - 32, Fade(BLACK, alpha));

        DrawRectangle(logo_position_x + 240, logo_position_y + 16, 16, right_side_height - 32, Fade(BLACK, alpha));
        DrawRectangle(logo_position_x, logo_position_y + 240, bottom_side_width, 16, Fade(BLACK, alpha));

        DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawText(TextSubtext("raylib", 0, letters_count), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, alpha));
        DrawTextEx(intro_font, "Powered by Raylib", (Vector2){(float)(GetScreenWidth()/2 - 170), (float)(GetScreenHeight()/2 + 150)}, 20, 1, Fade(BLACK, alpha));
    }

}