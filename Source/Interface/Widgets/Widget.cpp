
#include "Widget.h"

Widget::Widget() : local_position(Vector2I()) {}

Widget::Widget(Widget *_parent, Vector2I _local_position) :
        parent(_parent), local_position(_local_position) {

    parent->AddChild(this);
}


Widget::Widget(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height) :
        parent(_parent), local_position(_local_position), width(_width), height(_height),
        texture_id(ResourcesManager::zero_texture_id) {

    parent->AddChild(this);
}



Widget::Widget(Widget *_parent, Vector2I _local_position, size_t _texture_id, Vector2F scale) :
        parent(_parent), local_position(_local_position), texture_id(_texture_id) {

    parent->AddChild(this);

    scale = scale.Abs();
    height = round(ApplicationPtr->resources_manager->GetTexture(texture_id).getSize().y * scale.Y);
    width  = round(ApplicationPtr->resources_manager->GetTexture(texture_id).getSize().x * scale.X);
    sf::Vector2u size = ApplicationPtr->resources_manager->GetTexture(texture_id).getSize();
    sprite.setScale(Vector2F((double)width / size.x, (double)height / size.y));

    sprite.setTexture(ApplicationPtr->resources_manager->GetTexture(texture_id));
}

Widget::Widget(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height, size_t _texture_id) :
        parent(_parent), local_position(_local_position), width(_width), height(_height), texture_id(_texture_id) {

    parent->AddChild(this);

    size_t size_x = ApplicationPtr->resources_manager->GetTexture(texture_id).getSize().x;
    size_t size_y = ApplicationPtr->resources_manager->GetTexture(texture_id).getSize().y;
    sprite.setScale((float)width / size_x , (float)height / size_y);
    sprite.setTexture(ApplicationPtr->resources_manager->GetTexture(texture_id));
}

Widget::~Widget() {
}

void Widget::SetDelete() {
    is_delete = true;
    OnDelete();
}

void Widget::WorkDeleteChildren(){
    for (auto it = children.begin(); it != children.end();){
        Widget *child = *it;
        if (child->is_delete){
            it = children.erase(it);
            child->WorkDeleteChildren();
            delete child;
        }
        else {
            ++it;
            child->WorkDeleteChildren();
        }
    }
}

void Widget::SetDeleteChildrenFlags(bool deleteAll){
    for (auto it = children.begin(); it != children.end(); ++it){
        Widget *child = *it;
        if (deleteAll || child->is_delete){
            child->SetDeleteChildrenFlags(true);
            //child->is_delete = true;
            SetDelete();
        }
    }
}


void Widget::AddChild(Widget *widget) {
    children.push_back(widget);
}

void Widget::DrawChildren(sf::RenderWindow *window) {
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        Widget *child = *it;
        child->Draw(window);
        child->DrawChildren(window);
    }
}

void Widget::Draw(sf::RenderWindow *window) {
    window->draw(sprite);
}

bool Widget::isPosInParentInside(Vector2I pos_in_parent) const {
    return pos_in_parent.X >= local_position.X && pos_in_parent.Y >= local_position.Y &&
           pos_in_parent.X <= local_position.X + width && pos_in_parent.Y <= local_position.Y + height;
}

bool Widget::isPosInside(Vector2I pos) const {
    return pos.X >= 0 && pos.X <= width && pos.Y >= 0 && pos.Y <= height;
}

void Widget::SetNormal() {
    state = Normal;
}

void Widget::SetPressed() {
    state = Pressed;
}

void Widget::SetHovered() {
    state = Hovered;
}

bool Widget::WorkMousePressed(Mouse mouse, Widget *child) {

    Mouse childMouse(ConvertToChildPos(mouse.position, child), mouse.event);

    bool isInside = child->isPosInParentInside(mouse.position);
    if (isInside){
#ifdef MOUSE_DEBUG
        mouse.PrintInfo();
#endif
        child->SetPressed();
        child->OnPressBegin(childMouse);
    }

    child->WorkMouse(childMouse);
    return isInside;
}

bool Widget::WorkMouseReleased(Mouse mouse, Widget *child) {

    Mouse childMouse(ConvertToChildPos(mouse.position, child), mouse.event);

    bool isInside = child->isPosInParentInside(mouse.position);
    if (isInside) {
        if (child->GetState() == Widget::Pressed) {
#ifdef MOUSE_DEBUG
            mouse.PrintInfo();
#endif
            child->OnClicked();
        }
    }

    if (isInside) child->SetHovered();
    else          child->SetNormal();
    child->OnPressEnd(isInside, childMouse);

    child->WorkMouse(childMouse);
    return isInside;
}

bool Widget::WorkMouseMoved(Mouse mouse, Widget *child) {
#ifdef MOUSE_DEBUG
    mouse.PrintInfo();
#endif

    Mouse childMouse(ConvertToChildPos(mouse.position, child), mouse.event);

    bool isInside = child->isPosInParentInside(mouse.position);
    if (isInside){
        child->OnMouseMoved(childMouse);
        if (child->GetState() == Widget::Normal && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            child->SetHovered();
            child->OnHoverBegin(childMouse);
        }
    }
    else {
        if (child->GetState() == Widget::Hovered) {
            child->SetNormal();
            child->OnHoverEnd(childMouse);
        }
    }

    if (!child->was_mouse_inside && isInside) child->OnMouseIn(childMouse);
    if (child->was_mouse_inside && !isInside) child->OnMouseOut(childMouse);
    child->was_mouse_inside = isInside;

    child->WorkMouse(childMouse);
    return isInside;
}

void Widget::SetFirstInChildren() {
    if (GetType() != PANEL) return;
    if (parent == nullptr) return;
    for (auto it = parent->children.begin(); it != parent->children.end(); ++it)
        if (*it == this){
            Widget *child = *it;

            if (ApplicationPtr->logic_manager->FocusPanel != nullptr)
                ApplicationPtr->logic_manager->FocusPanel->SetFocus(false);

            ApplicationPtr->logic_manager->FocusPanel = child;
            child->SetFocus(true);

            parent->children.push_front(child);
            parent->children.erase(it);
            break;
        }
}

void Widget::WorkMouse(Mouse mouse) {

    for (auto it = children.begin(); it != children.end();) {
        Widget *child = *it;
        bool isInside = false, isPushed = false;
        if (mouse.event == Mouse::LEFT_BUTTON_PRESSED) {
            isInside = WorkMousePressed(mouse, child);
            if (isInside && child->GetType() == PANEL) {
                isPushed = true;

                if (ApplicationPtr->logic_manager->FocusPanel != nullptr)
                    ApplicationPtr->logic_manager->FocusPanel->SetFocus(false);

                ApplicationPtr->logic_manager->FocusPanel = child;
                child->SetFocus(true);

                children.push_front(child);
                it = children.erase(it);
            }
        }
        if (mouse.event == Mouse::LEFT_BUTTON_RELEASED){
            isInside = WorkMouseReleased(mouse, child);
        }
        if (mouse.event == Mouse::MOVED){
            isInside = WorkMouseMoved(mouse, child);
        }
        if (isInside) break;
        if (!isPushed) ++it;
    }
}

Widget::State Widget::GetState() const { return state; }

Widget *Widget::GetParent() {return parent;}

Vector2I Widget::GetLocalPosition() const { return local_position; }

Vector2I Widget::GetLocalCentrePosition() const { return Vector2I(local_position.X + width / 2, local_position.Y + height / 2); }

void Widget::SetLocalPosition(Vector2I pos) {
    local_position = pos;
    UpdatePos();
    UpdateChildrenPos();
}

void Widget::SetLocalCentrePosition(Vector2I pos){
    SetLocalPosition(Vector2I(pos.X - width / 2, pos.Y - height / 2));
}

Vector2I Widget::GetGlobalPosition() const {
    return parent != nullptr ? parent->GetGlobalPosition() + local_position : local_position;
}

void Widget::SetGlobalPosition(Vector2I pos) {
    local_position = pos - parent->GetGlobalPosition();
    UpdateChildrenPos();
}

Vector2I Widget::GetPosInParent(Vector2I pos) const{
    return pos - local_position;
}

Vector2I Widget::GetPosInGlobal(Vector2I pos) const{
    return pos + GetGlobalPosition();
}

void Widget::UpdatePos() {
    sprite.setPosition(GetGlobalPosition());
}

void Widget::UpdateChildrenPos() {
    for (Widget* child : children){
        child->UpdatePos();
        child->UpdateChildrenPos();
    }
}

size_t Widget::GetWidth() const { return width; }

size_t Widget::GetHeight() const { return height; }

Vector2I Widget::ConvertToChildPos(Vector2I pos, Widget *child) {
    return pos - child->local_position;
}

void Widget::SetScale(Vector2F new_scale) {
    new_scale = new_scale.Abs();

    Vector2F startScale = Vector2F((double)width / sprite.getTexture()->getSize().x,
                                   (double)height / sprite.getTexture()->getSize().y);

    sprite.setScale(startScale.X * new_scale.X, startScale.Y * new_scale.Y);
}

Widget::Type Widget::GetType() const { return type; }

void Widget::SetColor(Color color) {
    sprite.setColor(color);
}

void Widget::SetTexture(sf::Texture &_texture) {
    sprite.setTexture(_texture);
}

bool Widget::IsFocus() const { return is_focus; }

void Widget::SetFocus(bool new_focus) {
    is_focus = new_focus;
    if (is_delete) return;
    for (auto it = children.begin(); it != children.end(); ++it){
        Widget *child = *it;
        child->SetFocus(new_focus);
    }
}






