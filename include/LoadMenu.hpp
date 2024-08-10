#ifndef LOADMENU_H
#define LOADMENU_H

#include "State.hpp"
#include "Storage.hpp"

struct Load_btn {
    Rectangle rect;
    const char* text;
    Color baseColor;
    Color hoverColor;
    bool isHovered;

};

class LoadMenu : public State {
    private:
        std::shared_ptr<Storage> database;
        std::unordered_map<int, std::shared_ptr<Match>> match_list;
        std::deque<std::string> file_names;
        std::vector<Load_btn> buttons;
        int selectedMatch;
        Load_btn back_button;
    
    public:
        
        LoadMenu();
        ~LoadMenu() override;

        virtual void Process() override;

        virtual void Update() override;

        virtual void Render() override;

        std::shared_ptr<Match> getMatch();

};

#endif // LOADMENU_H