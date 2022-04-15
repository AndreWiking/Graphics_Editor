
#include "Utils2D.h"

void DrawCircle(sf::RenderTexture *texture, Vector2F pos, double radius, Color color) {
    sf::CircleShape shape(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(pos);
    shape.setFillColor(color);
    texture->draw(shape);
}

void DrawCircle(sf::RenderTexture *texture, size_t canvas_height, Vector2F pos, double radius, Color color) {
    DrawCircle(texture, ConvertToCanvasPos(pos, canvas_height), radius, color);
}

static const int RECTANGLE_POINTS_COUNT = 4;

Vector2F ConvertToCanvasPos(Vector2F pos, size_t canvas_height) {
    return Vector2F(pos.X, canvas_height - pos.Y);
}

void DrawLine(sf::RenderTexture *texture, size_t canvas_height, Vector2F startPoint, Vector2F endPoint, double thickness, Color color) {

    startPoint = ConvertToCanvasPos(startPoint, canvas_height);
    endPoint   = ConvertToCanvasPos(endPoint, canvas_height);

    DrawLine(texture, startPoint, endPoint, thickness, color);
}

void DrawLine(sf::RenderTexture *texture, Vector2F startPoint, Vector2F endPoint, double thickness, Color color) {


    sf::VertexArray line(sf::Quads, RECTANGLE_POINTS_COUNT);

    Vector2F dir = endPoint - startPoint;
    Vector2F normal = dir.GetNormal().Normalized() * thickness * 0.5;

    line[0].position = startPoint - normal;
    line[1].position = startPoint + normal;
    line[2].position = Vector2F(line[1].position.x, line[1].position.y) + dir;
    line[3].position = Vector2F(line[0].position.x, line[0].position.y) + dir;

    for (int i = 0; i < line.getVertexCount(); ++i)
        line[i].color = color;

    texture->draw(line);
    //DrawCircle(texture, startPoint, thickness / 2, color);
    DrawCircle(texture, endPoint, thickness / 2, color);
}
