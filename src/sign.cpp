#include "Sign.hpp"

Sign::Sign(const std::string &p_color) : color(p_color), owner(nullptr) {
    if (p_color == "black")
        icon = LoadTexture("../assets/pics/Wa_Sym.png");
    else if (p_color == "white")
        icon = LoadTexture("../assets/pics/Pe_Sym.png");
    else if (p_color == "Blue")
        icon = LoadTexture("../assets/pics/Blue_Sym.png");
    else if (p_color == "Red")
        icon = LoadTexture("../assets/pics/Red_Sym.png");
    else if (p_color == "Green")
        icon = LoadTexture("../assets/pics/Green_Sym.png");
    else if (p_color == "Gray")
        icon = LoadTexture("../assets/pics/Gray_Sym.png");
    else if (p_color == "Yellow")
        icon = LoadTexture("../assets/pics/Yellow_Sym.png");
    else if (p_color == "Purple")
        icon = LoadTexture("../assets/pics/Purple_Sym.png");
    else
        icon = LoadTexture("../assets/pics/dummy_Sym.png"); // Only for debugging
}

Sign::~Sign() {
    UnloadTexture(icon);
}

Texture2D Sign::getIcon() { return icon; }

void Sign::setOwner(std::shared_ptr<Player> p_owner) {
    owner = p_owner;
}

std::shared_ptr<Player> Sign::getOwner() const {
    return owner;
}

void Sign::setColor(const std::string& p_color) {
    this->color = p_color;
}

std::string Sign::getColor() const { return this->color; }