
#ifndef PANEL_H
#define PANEL_H

#include "../Widget.h"
#include "../Buttons/Button.h"
#include "PanelHeader.h"

class Panel : public Widget {
public:

    Panel(Widget* _parent, Vector2I _local_position, size_t _width, size_t _height, std::string name);

    void OnDelete() override;

protected:
    Button *close;
    PanelHeader *header;
    Text *title;

    static constexpr size_t HeaderHeight = 57;
    static constexpr Vector2I CloseButtonPos = {17, 17};
    static constexpr unsigned titleSize = 40;
};


#endif
