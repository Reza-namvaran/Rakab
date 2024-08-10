#include "LoadMenu.hpp"

LoadMenu::LoadMenu() : database(std::make_shared<Storage>()), selectedMatch(0) {
    status = 0;
    int counter = 0;
    this->file_names = this->database->getFilesNames();
    for (const std::string &fileName : this->file_names)
    {
        std::shared_ptr<Match> new_match = std::make_shared<Match>();
        this->database->loadMatch(new_match, fileName);
        this->match_list[0] = new_match;

        int i = 1;
        buttons.push_back((Load_btn){{50, (float)100 * i, 200, 50}, fileName.c_str(), LIGHTGRAY, RED, false});
        counter++;
    }
}

LoadMenu::~LoadMenu() {}

void LoadMenu::Process() {
Vector2 mousePoint = GetMousePosition();
    for (int i = 0; i < buttons.size(); i++) {
        if (CheckCollisionPointRec(mousePoint, buttons[i].rect)) {
            buttons[i].isHovered = true;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Handle button click
                selectedMatch = i;
                status = 6;
            }
        } else {
            buttons[i].isHovered = false;
        }
    }
}

void LoadMenu::Update() {}

void LoadMenu::Render() {
    for (size_t idx = 0; idx < buttons.size(); ++idx) {
        DrawRectangleRec(buttons[idx].rect, buttons[idx].isHovered ? buttons[idx].hoverColor : buttons[idx].baseColor);
        int textWidth = MeasureText(buttons[idx].text, 20)  ;
        int textHeight = 20;
        DrawText(buttons[idx].text, buttons[idx].rect.x + (buttons[idx].rect.width - textWidth) / 2, buttons[idx].rect.y + (buttons[idx].rect.height - textHeight) / 2, 20, BLACK);
    }
}

std::shared_ptr<Match> LoadMenu::getMatch() {
    return match_list[selectedMatch];
}