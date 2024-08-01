#ifndef STATE_H
#define STATE_H

#include <raylib.h>

typedef struct Button {
    Rectangle rect;
    const char* text;
    bool hover;
};

/// DESCRIPTION: State Design Pattern
class State {
    public:
        State() {}
        ~State() = default;

        virtual void EnterState() = 0;

        virtual void Process() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;

        virtual void ExitState() = 0;

};

#endif // STATE_H