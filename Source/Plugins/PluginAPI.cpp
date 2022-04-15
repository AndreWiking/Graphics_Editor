
#include "PluginAPI.h"

bool enable(const char *name) { return false; }

void *get_func(const char *extension, const char *func) { return nullptr; }

void log(const char *fmt, ...) { }

double get_absolute_time() {
    return Settings->GlobalClock.getElapsedTime().asSeconds();
}

void release_pixels(PRGBA *pixels) {
    free(pixels);
}

PRGBA get_color() {
    Color color = Settings->BrushColor;
    return PRGBA(color.R, color.G, color.B, color.A);
}

float get_brush_size() {
    return Settings->BrushSize;
}

PRGBA *get_pixels() {
    sf::Image canvas_image = Settings->Paint_canvas_texture->getTexture().copyToImage();
    PRGBA *pixels = new PRGBA[canvas_image.getSize().y * canvas_image.getSize().x];

    for (size_t y = 0; y <  canvas_image.getSize().y; ++y)
        for (size_t x = 0; x <  canvas_image.getSize().x; ++x) {
            Color color = Color(canvas_image.getPixel(x, y));
            //((PRGBA**)pixels)[y][x] = PRGBA(color.R, color.G, color.B, color.A);
            pixels[y * canvas_image.getSize().x + x] = PRGBA(color.R, color.G, color.B, color.A);
        }

    return pixels;
}

void get_canvas_size(size_t *width, size_t *height) {
    *width  = Settings->Paint_canvas_texture->getSize().x;
    *height = Settings->Paint_canvas_texture->getSize().y;
}

void pixels(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode) {
    if (render_mode->draw_policy == PPDP_ACTIVE){
        InverseCord(&position);
    }

    sf::RenderTexture *texture = GetTexture(render_mode);

    sf::Image image;
    image.create(width, height, sf::Color::Transparent);
    for (size_t y = 0; y < height; ++y)
        for (size_t x = 0; x < width; ++x) {
            PRGBA color = data[y * width + x];

            if (render_mode->blend == PPBM_COPY)
                image.setPixel(x, y, {color.r, color.g, color.b, UINT8_MAX});
            else
                image.setPixel(x, y, {color.r, color.g, color.b, color.a});
        }

    sf::Texture new_texture;
    new_texture.create(width, height);
    new_texture.update(image);
    sf::Sprite sprite(new_texture);
    sprite.setPosition(position.x, position.y);
    if (render_mode->draw_policy == PPDP_ACTIVE)
        sprite.setScale(1, -1);
    texture->draw(sprite);
}

void circle(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode) {
    if (render_mode->draw_policy == PPDP_ACTIVE){
        InverseCord(&position);
    }
    sf::RenderTexture *texture = GetTexture(render_mode);

    sf::CircleShape shape(radius);
    shape.setFillColor(GetColor(color, render_mode));
    shape.setPosition(position.x - radius / 2, position.y - radius / 2);

    texture->draw(shape);
}

static const double LINE_THICKNESS = 5;

void line(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode) {
    if (render_mode->draw_policy == PPDP_ACTIVE){
        InverseCord(&start);
        InverseCord(&end);
    }
    sf::RenderTexture *texture = GetTexture(render_mode);

    DrawLine(texture, {start.x, start.y}, {end.x, end.y}, LINE_THICKNESS, GetColor(color, render_mode));
}

void triangle(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode) {
    if (render_mode->draw_policy == PPDP_ACTIVE){
        InverseCord(&p1);
        InverseCord(&p2);
        InverseCord(&p3);
    }
    sf::RenderTexture *texture = GetTexture(render_mode);

    sf::ConvexShape convex(3);
    convex.setPoint(0, {p1.x, p1.y});
    convex.setPoint(1, {p2.x, p2.y});
    convex.setPoint(2, {p3.x, p3.y});

    convex.setFillColor(GetColor(color, render_mode));
    texture->draw(convex);
}

void rectangle(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode) {
    if (render_mode->draw_policy == PPDP_ACTIVE){
        InverseCord(&p1);
        InverseCord(&p2);
    }
    sf::RenderTexture *texture = GetTexture(render_mode);

    sf::RectangleShape rectangle({p2.x - p1.x, p2.y - p1.y});
    rectangle.setPosition(p1.x, p2.x);
    rectangle.setFillColor(GetColor(color, render_mode));
    texture->draw(rectangle);
}

sf::RenderTexture *GetTexture(const PRenderMode *render_mode) {
    if (render_mode->draw_policy == PPDP_PREVIEW)
        return Settings->Paint_canvas_preview_texture;
    else
        return Settings->Paint_canvas_texture;
}

Color GetColor(PRGBA color, const PRenderMode *render_mode) {
    Color col(color);
    if (render_mode->blend == PPBM_COPY)
        col.A = UINT8_MAX;
    return col;
}

void InverseCord(PVec2f *vec){
    vec->y = Settings->Paint_canvas_texture->getSize().y - vec->y;
}