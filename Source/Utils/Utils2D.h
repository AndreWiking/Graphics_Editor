
#ifndef UTILS2D_H
#define UTILS2D_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Color.h"

void DrawCircle(sf::RenderTexture *texture, Vector2F pos, double radius, Color color);
void DrawCircle(sf::RenderTexture *texture, size_t canvas_height, Vector2F pos, double radius, Color color);

void DrawLine(sf::RenderTexture *texture, size_t canvas_height, Vector2F startPoint, Vector2F endPoint, double thickness, Color color);
void DrawLine(sf::RenderTexture *texture, Vector2F startPoint, Vector2F endPoint, double thickness, Color color);

Vector2F ConvertToCanvasPos(Vector2F pos, size_t canvas_height);

#endif //UTILS2D_H
