#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.hpp"

class MainMenu : public State {
    public:
        MainMenu();
        ~MainMenu() override;

        virtual void EnterState() override;

        virtual void Process() override;
        virtual void Update() override;
        virtual void Render() override;

        virtual void ExitState() override;
    
    private:
        int NUM_BACKGROUNDS;
        int CHANGE_INTERVAL;
        bool wants_to_exit;
        Music main_menu_music;
        Sound button_sound;
        Font canterbury_font;
        Texture2D backgrounds[3];
        int selected_button = -1;
        int current_background = 0;
        int next_background = (current_background + 1) % 3;
        float changeTimer = 0.0f;
        float fadeAlpha = 0.0f;
        Button buttons[3];
};

#endif // MAINMENU_H
