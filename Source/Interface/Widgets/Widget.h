
#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>
#include "../../Utils/Color.h"
#include "../Utils/Mouse.h"
#include "../Controllers/ResourcesManager.h"
#include "../Controllers/LogicManager.h"
#include "../Utils/Application.h"
#include <iostream>
#include <list>

//#define MOUSE_DEBUG

extern Application *ApplicationPtr;

class Widget {
public:

    Widget();

    Widget(Widget* _parent, Vector2I _local_position);

    Widget(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height);

    Widget(Widget* _parent, Vector2I _local_position, size_t _texture_id, Vector2F scale);

    Widget(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height, size_t _texture_id);

    virtual ~Widget();

    void SetDelete();
    void WorkDeleteChildren();
    void SetDeleteChildrenFlags(bool deleteAll);

    void DrawChildren(sf::RenderWindow *window);

    virtual void Draw(sf::RenderWindow *window);

    void SetFirstInChildren();

    void WorkMouse(Mouse mouse);

    void UpdateChildrenPos();

    virtual void SetScale(Vector2F scale);

    void SetColor(Color color);

    void SetTexture(sf::Texture &_texture);

    Widget* GetParent();

    Vector2I GetLocalPosition() const;
    Vector2I GetLocalCentrePosition() const;
    void     SetLocalPosition(Vector2I pos);
    void     SetLocalCentrePosition(Vector2I pos);

    virtual Vector2I GetGlobalPosition() const;
    virtual void     SetGlobalPosition(Vector2I pos);

    Vector2I GetPosInParent(Vector2I pos) const;
    Vector2I GetPosInGlobal(Vector2I pos) const;

    enum ErrorCode{ NEGATIVE_SCALE, PARENT_NULLPTR, CHILD_NULLPTR };
    enum State{ Normal, Hovered, Pressed };
    enum Type{ WIDGET, PANEL};

    State GetState() const;

    size_t GetWidth()  const;
    size_t GetHeight() const;

    Type GetType() const;

    bool IsFocus() const;
    void SetFocus(bool new_focus);

protected:
    Type type = WIDGET;
    Vector2I local_position; // position in parent
    size_t width, height;
    State state = Normal;

    sf::Sprite sprite;
    size_t texture_id;

    Widget* parent;
    std::list<Widget*> children;
    bool is_delete = false;
    bool is_focus = false;

    void AddChild(Widget *widget);

    virtual void SetNormal();

    virtual void SetPressed();

    virtual void SetHovered();


    virtual void OnMouseMoved(Mouse mouse) {}

    virtual void OnHoverBegin(Mouse mouse) {}

    virtual void OnHoverEnd(Mouse mouse) {}

    virtual void OnPressBegin(Mouse mouse) {}

    virtual void OnPressEnd(bool is_inside, Mouse mouse) {}

    virtual void OnClicked() {}

    virtual void OnGlobalMouseMoved(Mouse global_mouse) {}

    virtual void OnMouseOut(Mouse mouse) {}

    virtual void OnMouseIn(Mouse mouse) {}

    virtual void OnDelete() {}


    bool WorkMousePressed(Mouse mouse, Widget* child);

    bool WorkMouseReleased(Mouse mouse, Widget* child);

    bool WorkMouseMoved(Mouse mouse, Widget* child);

    bool isPosInParentInside(Vector2I pos_in_parent) const;
    bool isPosInside(Vector2I pos) const;

    static Vector2I ConvertToChildPos(Vector2I pos, Widget *child);

    virtual void UpdatePos();


    friend class GuiManager;

private:
    bool was_mouse_inside = false;
    Vector2F prev_mouse_moved_pos;
};

class RootWidget : public Widget{
public:

    RootWidget(size_t _background_id, size_t _width, size_t _height) {
        width = _width;
        height = _height;

        sprite.setTexture(ApplicationPtr->resources_manager->GetTexture(_background_id));
    }

    Vector2I GetGlobalPosition() const override {return Vector2I();}

protected:
};



#endif
