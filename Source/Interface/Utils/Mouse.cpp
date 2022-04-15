
#include "Mouse.h"

void Mouse::PrintInfo() const {
    std::cout << "Mouse (" << position.X << ", " << position.Y << ") ";
    switch (event) {
        case LEFT_BUTTON_PRESSED:
            std::cout << "Pressed\n";
            break;
        case LEFT_BUTTON_RELEASED:
            std::cout << "Released\n";
            break;
        case MOVED:
            std::cout << "Moved\n";
            break;
    }
}
