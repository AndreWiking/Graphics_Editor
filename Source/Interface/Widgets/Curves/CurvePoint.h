#ifndef CURVE_POINT_H
#define CURVE_POINT_H


#include "../Buttons/Button.h"

class CurvePoint : public Button{
public:

    CurvePoint(Widget *_parent, Vector2I _local_position)
        : Button(_parent, _local_position, ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::CURVE_POINT),
                 ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::CURVE_POINT_PRESSED), Scale) {

    }

    void OnPressBegin(Mouse mouse) override {
        is_moving = true;
        move_offset = mouse.position - Vector2I(width / 2, height / 2);
    }

    void OnPressEnd(bool is_inside, Mouse mouse) override {
        is_moving = false;
    }

    void MoveToPosition(Vector2I pos){
        *curve_points_pos_it = pos;
        SetLocalCentrePosition(pos);
    }

    bool is_moving = false;
    Vector2I move_offset;
    std::list<CurvePoint*>::const_iterator curve_points_it;
    std::list<Vector2I>::iterator curve_points_pos_it;
protected:
    static constexpr Vector2F Scale = {1, 1};
private:

};


#endif
