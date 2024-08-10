#ifndef PLAYERSETUP_H
#define PLAYERSETUP_H

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#include "State.hpp"
#include "Player.hpp"

class PlayerSetup : public State {
  public:
    PlayerSetup();
    virtual ~PlayerSetup() override;

    virtual void Process() override;
    virtual void Update() override;
    virtual void Render() override;
    std::vector<std::shared_ptr<Player>> getData();

  private:
    // void resetAllData();
    void resetFields();

    int number_of_players;
    int temp_number_of_players;
    std::vector<std::shared_ptr<Player>> players;

    /// NOTE: One extra space required for null terminator char '\0'
    char name_buffer[51] = "\0";
    char age_buffer[4] = "\0";

    int letter_count;
    int number_count;

    Rectangle text_box;
    Rectangle age_box;

    bool mouse_on_text;
    bool mouse_on_age;

    // Drop down menu for selecting colors and number of players
    // ---------------------------------------
    std::vector<std::string> color_option;
    std::string selected_color;
    std::vector<std::string> player_nums;
    std::string selected_number;

    bool is_color_menu_open;
    bool is_player_num_open;

    Rectangle drop_down_bounds;
    Rectangle number_menu_bounds;
    std::vector<Rectangle> option_bounds;
    std::vector<Rectangle> number_rects_bounds;
    // ---------------------------------------
    Button Confirm;
    bool is_confirmed;
    int confirm_count;
    Color color {65, 105, 225, 255};

    Texture2D background;

    std::unordered_map<std::string, Texture2D> characters;

    int frames_counter;
};

#endif // PLAYERSETUP_H
