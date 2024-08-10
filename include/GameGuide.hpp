#ifndef GAMEGUIDE_H
#define GAMEGUIDE_H

#include <vector>

#include "raylib.h"

struct btn {
    Rectangle rect;
    const char* text;
    bool hover;
};

class GameGuide {
  private:
    Font canterbury_font;
    std::vector<Texture2D> images;
    int currentImageIndex;
    Texture2D currentImage;
    btn next_button;
    btn previous_button;
    btn back_button;
    int state;


  public:
    GameGuide();

    void getGuidline();

    int getStatus() const;

    void setStatus(int status);

    void render();

    ~GameGuide();
};

#endif // GAMEGUIDE_H
