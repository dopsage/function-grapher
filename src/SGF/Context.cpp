
#include "SGF/Context.hpp"

using namespace sgf;

Context::   Context() :
            sfmlWindowPtr(nullptr)
{
    
}

void Context::line(Vector2D start, Vector2D end, Color3D color, int thickness)
{
    Vector2D    vDir        = { end.x - start.x, end.y - start.y };
    float       degAngle    = std::atan2(vDir.y, vDir.x) * 180.0f / 3.141593f;
    
    // Form a line with specified thickness and color using a rotated rectangle shape
    sf::RectangleShape rect(sf::Vector2f(
        std::sqrt(vDir.x * vDir.x + vDir.y * vDir.y),
        thickness
    ));
    rect.setPosition    (sf::Vector2f(start.x, start.y));
    rect.setFillColor   (sf::Color(color.r, color.g, color.b));
    rect.setRotation    (degAngle);
    
    sfmlWindowPtr->draw(rect);
}
