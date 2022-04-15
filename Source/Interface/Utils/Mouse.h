
#ifndef MOUSE_H
#define MOUSE_H

#include "../../Utils/Vector2.h"
#include <iostream>

class Mouse {
public:

    Vector2I position;

    Mouse() {}

    enum Event{
        LEFT_BUTTON_PRESSED, LEFT_BUTTON_RELEASED, MOVED
    };

    Event event;

    Mouse(Vector2I _position, Event _event) : position(_position), event(_event){}

    void PrintInfo() const;
};


#endif
