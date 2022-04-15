#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <SFML/Window/Event.hpp>
#include "../Widgets/Widget.h"

class GuiManager{
public:
    static GuiManager *Instance();
    static bool DeleteInstance();

    void WorkMouseEvent(const sf::Event &event);

    void SetWindow(sf::RenderWindow *_window);
    void SetRootWidget(RootWidget *_root);

    void Draw();

    void WorkDeleteWidgets();


    enum Event{
        ON_MOUSE_MOVED = 0, EVENT_COUNT
    };

    enum ErrorCode{
        ROOT_NULLPTR
    };

    void AddSubscribedWidget(Widget *widget, Event event);

    Widget *GetRoot();

private:
    static GuiManager *_self;

    RootWidget *root;
    sf::RenderWindow *window;
    Mouse mouse;

    std::list<Widget*> event_subscribed[EVENT_COUNT];

    GuiManager(){}
    GuiManager(sf::RenderWindow *_window) : window(_window) {}

    ~GuiManager(){ }


    void WorkDeleteSubscribedWidgets();

    void WorkSubscribedEvent(Event event);
};

#endif