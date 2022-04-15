
#ifndef LOGIC_MANAGER_H
#define LOGIC_MANAGER_H

#include <list>
#include "../../Utils/Vector2.h"

class Widget;
class CurvePoint;

class LogicManager {
public:
    static LogicManager *Instance();
    static bool DeleteInstance();

    Widget* FocusPanel = nullptr;

    enum OpenPanel { PAINT_CANVAS, BRUSH_SIZE , COLOR_PICKER, TOOLBAR, CURVES, OPEN_PANEL_COUNT };

    bool isPanelOpen[OPEN_PANEL_COUNT] = {};

    std::list<Vector2I> *Saved_curve_points_pos = nullptr;


private:
    static LogicManager *_self;

    LogicManager(){ }

    ~LogicManager(){
        if (Saved_curve_points_pos != nullptr)
            delete Saved_curve_points_pos;
    }
};



#endif
