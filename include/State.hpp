#ifndef STATE_H
#define STATE_H

#include <raylib.h>

struct Button {
    Rectangle rect;
    const char* text;
    bool hover;
};

/// DESCRIPTION: State Design Pattern
class State {
    public:
        virtual ~State() = default;

        virtual void Process() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;

        int getStatus();

    protected:
        int screenHeight = 900;
        int screenWidth = 1400;
        int status;
};

#endif // STATE_H
