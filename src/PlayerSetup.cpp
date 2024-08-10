#include "PlayerSetup.hpp"

PlayerSetup::PlayerSetup() : number_of_players(0), temp_number_of_players(0), letter_count(0), number_count(0), is_player_num_open(false),
is_color_menu_open(false), mouse_on_text(false), mouse_on_age(false), frames_counter(0), is_confirmed(false), confirm_count(0) {
    status = 0;
    this->text_box = { 20, 180, 900, 50 };
    this->age_box = { 930, 180, 65, 50};
    this->selected_color = "Select a color";
    this->selected_number = "number of players";

    this->drop_down_bounds = {1000, 180, 200, 50};
    this->option_bounds = {
        {1000, 180 + 50, 200, 50},
        {1000, 180 + 100, 200, 50},
        {1000, 180 + 150, 200, 50},
        {1000, 180 + 200, 200, 50},
        {1000, 180 + 250, 200, 50},
        {1000, 180 + 300, 200, 50},
    };

    this->number_menu_bounds = {10, 10, 200, 25};
    this->number_rects_bounds = {
        {10, 10 + 25, 200, 25},
        {10, 10 + 50, 200, 25},
        {10, 10 + 75, 200, 25},
        {10, 10 + 100, 200, 25},
    };


    this->color_option = {"Blue", "Red", "Green", "Yellow", "Gray", "Purple"};
    this->player_nums = {"3", "4", "5", "6"};


    Confirm = {(Rectangle){1200, 180, 150, 50}, "Confirm", false};
    back_button = {(Rectangle){10, 840, 150, 50}, "Back", false};


    this->characters = {
        {"Blue", LoadTexture("../assets/pics/blue.png")},
        {"Red", LoadTexture("../assets/pics/red.png")},
        {"Green", LoadTexture("../assets/pics/green.png")},
        {"Yellow", LoadTexture("../assets/pics/yellow.png")},
        {"Gray", LoadTexture("../assets/pics/gray.png")},
        {"Purple", LoadTexture("../assets/pics/purple.png")},
    };

    background = LoadTexture("../assets/pics/castle.png");
}

PlayerSetup::~PlayerSetup() {
    for(std::string color : (std::vector<std::string>){"Blue", "Red", "Green", "Yellow", "Gray", "Purple"})
    {
        UnloadTexture(characters[color]);
    }

    UnloadTexture(background);
}

void PlayerSetup::Process() {
    if (CheckCollisionPointRec(GetMousePosition(), text_box)) 
        mouse_on_text = true;
    else 
        mouse_on_text = false;

    if (CheckCollisionPointRec(GetMousePosition(), age_box)) 
        mouse_on_age = true;
    else 
        mouse_on_age = false;

    if (CheckCollisionPointRec(GetMousePosition(), Confirm.rect))
    {
        Confirm.hover = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (name_buffer[0] != '\0' && age_buffer[0] != '\0' && age_buffer[0] != '0' && selected_color != "Select a color" && selected_color.length() > 0 && number_of_players != 0)
            {

                auto new_player = std::make_shared<Player>(name_buffer, std::stoul(age_buffer), selected_color);
                players.emplace_back(new_player);
                confirm_count++;
                color_option.erase(std::remove(color_option.begin(), color_option.end(), selected_color), color_option.end());
                resetFields();
            }
        }
    }
    else
        Confirm.hover = false;

    if (CheckCollisionPointRec(GetMousePosition(), back_button.rect))
    {
        back_button.hover = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            status = 2;
        }
    }
    else
        back_button.hover = false;
}

void PlayerSetup::Update() {
    if (mouse_on_text || mouse_on_age)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            /// NOTE: Only allow keys in range [32..125] for name field
            if ((key >= 32) && (key <= 125) && (letter_count < 50) && mouse_on_text)
            {
                name_buffer[letter_count] = (char)key;
                name_buffer[letter_count + 1] = '\0'; // Add null terminator at the end of the string.
                letter_count++;
            }
            // Age field
            else if ((key >= 48) && (key <= 57) && (number_count < 3) && mouse_on_age)
            {
                age_buffer[number_count] = (char)key;
                age_buffer[number_count + 1] = '\0'; // Add null terminator at the end of the string.
                number_count++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (mouse_on_text)
            {
                letter_count--;
                if (letter_count < 0) 
                    letter_count = 0;
                name_buffer[letter_count] = '\0';
            }
            else if (mouse_on_age)
            {
                number_count--;
                if (number_count < 0)
                    number_count = 0;
                age_buffer[number_count] = '\0';
            }
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);


    if (mouse_on_text || mouse_on_age) frames_counter++;
    else frames_counter = 0;

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(GetMousePosition(), drop_down_bounds)) {
                is_color_menu_open = !is_color_menu_open;  // Toggle dropdown open/close
            } else if (is_color_menu_open) {
                // Check if the click is within one of the option bounds
                for (int i = 0; i < color_option.size(); i++) {
                    if (CheckCollisionPointRec(GetMousePosition(), option_bounds[i])) {
                        selected_color = color_option[i];  // Set selected option on click
                        is_color_menu_open = false;        // Close the dropdown
                        break;
                    }
                }
            }
        }
    
    if (number_of_players == 0)
    {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(GetMousePosition(), number_menu_bounds)) {
                    is_player_num_open = !is_player_num_open;  // Toggle dropdown open/close
                } else if (is_player_num_open) {
                    // Check if the click is within one of the option bounds
                    for (int i = 0; i < player_nums.size(); i++) {
                        if (CheckCollisionPointRec(GetMousePosition(), number_rects_bounds[i])) {
                            selected_number = player_nums[i];  // Set selected option on click
                            number_of_players = std::stoi(selected_number);
                            is_player_num_open = false;        // Close the dropdown
                            break;
                        }
                    }
                }
            }
    }
}

void PlayerSetup::Render() {
    Rectangle sourceRec = { 0.0f, 0.0f, (float)background.width, (float)background.height };
    Rectangle destRec = { 0.0f, 0.0f, (float)1400, (float)900 };

    DrawTexturePro(background, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);


    // Draw input fields
    DrawRectangleRec(text_box, LIGHTGRAY);
    DrawRectangleRec(age_box, LIGHTGRAY);

    DrawRectangleRec(back_button.rect, back_button.hover ? RED : LIGHTGRAY);
    DrawText(back_button.text, back_button.rect.x + 10, back_button.rect.y + 10, 30, BLACK);
    

    if (!this->Confirm.hover)
        DrawRectangleRec(Confirm.rect, (Color){120, 220, 145, 255});
    else
        DrawRectangleRec(Confirm.rect, GREEN);

    // Hover input fields
    if (mouse_on_text) 
        DrawRectangleLines((int)text_box.x, (int)text_box.y, (int)text_box.width, (int)text_box.height, BLUE);
    else
        DrawRectangleLines((int)text_box.x, (int)text_box.y, (int)text_box.width, (int)text_box.height, DARKGRAY);

    if (mouse_on_age) 
        DrawRectangleLines((int)age_box.x, (int)age_box.y, (int)age_box.width, (int)age_box.height, BLUE);
    else
        DrawRectangleLines((int)age_box.x, (int)age_box.y, (int)age_box.width, (int)age_box.height, DARKGRAY);

    // Write input
    DrawText(name_buffer, (int)text_box.x + 5, (int)text_box.y + 8, 30, color);
    DrawText(age_buffer, (int)age_box.x + 5, (int)age_box.y + 8, 30, color);

    DrawText(Confirm.text, (int)Confirm.rect.x + 10, (int)Confirm.rect.y + 10, 30, WHITE);

    // Draw blinking cursor
    if (mouse_on_text)
    {
        if (((frames_counter/20)%2) == 0) 
            DrawText("|", (int)text_box.x + 8 + MeasureText(name_buffer, 30), (int)text_box.y + 12, 30, color);
    }
    else if (mouse_on_age)
    {
        if (((frames_counter/20)%2) == 0) 
            DrawText("|", (int)age_box.x + 8 + MeasureText(age_buffer, 30), (int)age_box.y + 12, 30, color);
    }

    DrawRectangleRec(drop_down_bounds, LIGHTGRAY);
    DrawRectangleLinesEx(drop_down_bounds, 2, DARKGRAY);
    DrawText(selected_color.c_str(), drop_down_bounds.x + 5, drop_down_bounds.y + 5, 25, BLACK);

    // Draw the options if the dropdown is open
    if (is_color_menu_open) {
        for (int i = 0; i < color_option.size(); i++) {
            DrawRectangleRec(option_bounds[i], LIGHTGRAY);
            DrawRectangleLinesEx(option_bounds[i], 1, DARKGRAY);
            DrawText(color_option[i].c_str(), option_bounds[i].x + 5, option_bounds[i].y + 5, 30, BLACK);
        }
    }

    if (number_of_players == 0)
    {
        DrawRectangleRec(number_menu_bounds, LIGHTGRAY);
        DrawRectangleLinesEx(number_menu_bounds, 2, DARKGRAY);
        DrawText(selected_number.c_str(), number_menu_bounds.x + 5, number_menu_bounds.y + 5, 20, BLACK);

        // Draw the options if the dropdown is open
        if (is_player_num_open) {
            for (int i = 0; i < player_nums.size(); i++) {
                DrawRectangleRec(number_rects_bounds[i], LIGHTGRAY);
                DrawRectangleLinesEx(number_rects_bounds[i], 1, DARKGRAY);
                DrawText(player_nums[i].c_str(), number_rects_bounds[i].x + 5, number_rects_bounds[i].y + 5, 20, BLACK);
            }
        }
    }

    if(selected_color != "Select a color")
    {
        DrawTexture(characters[selected_color], 350, 375, WHITE);
    }

    if (confirm_count == number_of_players && number_of_players != 0)
        status = 5;
    
}

void PlayerSetup::resetFields() {
    this->letter_count = 0;
    this->number_count = 0;
    this->selected_color = "Select a color";
    name_buffer[0] = '\0';
    age_buffer[0] = '\0';
    this->is_color_menu_open = false;
}

std::vector<std::shared_ptr<Player>> PlayerSetup::getData() {
    return this->players;
}