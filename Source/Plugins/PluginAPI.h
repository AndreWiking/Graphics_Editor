
#ifndef PLUGIN_API_H
#define PLUGIN_API_H

#include <SFML/Graphics.hpp>
#include <plugin_std.h>
#include "../Utils/Color.h"
#include "../Utils/Utils2D.h"
#include "../Interface/Settings/GlobalSettings.h"
//#include "../Interface/Utils/Application.h"

//extern Application *ApplicationPtr;
extern GlobalSettings *Settings;

bool enable(const char *name);
void *get_func(const char *extension, const char *func);

void log(const char *fmt, ...);
double get_absolute_time();

void release_pixels(PRGBA *pixels);

PRGBA get_color();

float get_brush_size();

PRGBA *get_pixels();

void get_canvas_size(size_t *width, size_t *height);

void pixels(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode);

void circle(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode);
void line(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode);
void triangle(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode);
void rectangle(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode);

sf::RenderTexture *GetTexture(const PRenderMode *render_mode);
Color GetColor(PRGBA color, const PRenderMode *render_mode);
void InverseCord(PVec2f *vec);

const struct PAppInterface app_interface{
        .std_version = 0,
        .reserved = nullptr,

        .extensions{
                .enable = &enable,
                .get_func = &get_func
        },

        .general{
                .feature_level = 0,

                .log = &log,
                .get_absolute_time = &get_absolute_time,

                .release_pixels = &release_pixels,

                .get_color = &get_color,
                .get_size = &get_brush_size,
        },

        .target{
                .get_pixels = &get_pixels,
                .get_size = &get_canvas_size,
        },

        .render{
                .circle = &circle,
                .line = &line,
                .triangle = &triangle,
                .rectangle = &rectangle,

                .pixels = &pixels,
        },

        .settings {
                .create_surface = nullptr,
                .destroy_surface = nullptr,

                .add = nullptr,
                .get = nullptr
        },

        .shader{
                .apply = nullptr,

                .compile = nullptr,
                .release = nullptr,

                .set_uniform_int = nullptr,
                .set_uniform_int_arr = nullptr,

                .set_uniform_float = nullptr,
                .set_uniform_float_arr = nullptr,
        }
};


#endif
