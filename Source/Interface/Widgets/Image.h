
#ifndef IMAGE_H
#define IMAGE_H

#include "Widget.h"

class Image : public Widget{
public:

    Image(Widget* _parent, Vector2I _local_position, size_t _texture_id) :
            Widget(_parent, _local_position, _texture_id, Vector2F(1, 1)){}

    Image(Widget* _parent, Vector2I _local_position, size_t _texture_id, Vector2F scale) :
            Widget(_parent, _local_position, _texture_id, scale){}

    Image(Widget* _parent, Vector2I _local_position, size_t _width, size_t _height, size_t _texture_id) :
            Widget(_parent, _local_position, _width, _height, _texture_id){}

protected:
};



#endif //IMAGE_H
