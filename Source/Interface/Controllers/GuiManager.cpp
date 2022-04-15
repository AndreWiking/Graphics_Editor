
#include "GuiManager.h"

GuiManager* GuiManager::_self = nullptr;

GuiManager *GuiManager::Instance() {
    if (!_self) {
        _self = new GuiManager();
    }
    return _self;
}

bool GuiManager::DeleteInstance() {
    if (_self) {
        delete _self;
        _self = 0;
        return true;
    }
    return false;
}

void GuiManager::WorkMouseEvent(const sf::Event &event) {
    if (root == nullptr) throw ROOT_NULLPTR;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        mouse = Mouse(Vector2I(event.mouseButton.x, event.mouseButton.y), Mouse::LEFT_BUTTON_PRESSED);
        root->WorkMouse(mouse);
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        mouse = Mouse(Vector2I(event.mouseButton.x, event.mouseButton.y), Mouse::LEFT_BUTTON_RELEASED);
        root->WorkMouse(mouse);
    }

    if (event.type == sf::Event::MouseMoved) {
        mouse = Mouse(Vector2I(event.mouseMove.x, event.mouseMove.y), Mouse::MOVED);

        WorkSubscribedEvent(ON_MOUSE_MOVED);
        root->WorkMouse(mouse);
    }
}

void GuiManager::WorkSubscribedEvent(GuiManager::Event event) {
    for (Widget* widget : event_subscribed[event])
        if (widget->is_focus)
            switch (event) {
                case ON_MOUSE_MOVED:
                    widget->OnGlobalMouseMoved(mouse);
                    break;
                case EVENT_COUNT:
                    break;
            }
}


void GuiManager::SetRootWidget(RootWidget *_root) {
    root = _root;
}

void GuiManager::SetWindow(sf::RenderWindow *_window) {
    window = _window;
}

void GuiManager::Draw() {
    if (root == nullptr) throw ROOT_NULLPTR;

    root->Draw(window);
    root->DrawChildren(window);
}

void GuiManager::WorkDeleteWidgets() {
    root->SetDeleteChildrenFlags(false);
    WorkDeleteSubscribedWidgets();
    root->WorkDeleteChildren();
}

void GuiManager::WorkDeleteSubscribedWidgets() {
    for (int i = 0; i < EVENT_COUNT; ++i)
        for (auto it = event_subscribed[i].begin(); it != event_subscribed[i].end();){
            Widget *widget = *it;
            if (widget->is_delete)
                it = event_subscribed[i].erase(it);
            else
                ++it;
        }
}

void GuiManager::AddSubscribedWidget(Widget *widget, GuiManager::Event event) {
    event_subscribed[event].push_back(widget);
}

Widget *GuiManager::GetRoot() {
    return root;
}



