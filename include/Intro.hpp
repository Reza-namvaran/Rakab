#ifndef INTRO_H
#define INTRO_H

#include "State.hpp"

class Intro : public State {
  public:
    Intro();
    ~Intro() override;

    virtual void Process() override;
    virtual void Update() override;
    virtual void Render() override;

  private:
    Font intro_font;

    // Logo position
    int logo_position_x;
    int logo_position_y;

    int frames_counter;
    int letters_count;

    // Raylib logo size
    int top_side_width;
    int bottom_side_width;
    int right_side_height;
    int left_side_height;

    int state;               // Tracking animation states (State MAchine)
    float alpha;             // For fading
};

#endif // INTRO_H
