
#include "SGF/Rectangle.hpp"

sgf::Rectangle::Rectangle() : 
           color({0, 0, 0}),
keyboardListener(nullptr),
 keyboardPayload(nullptr),
   mouseListener(nullptr),
    mousePayload(nullptr),
        position({0.F, 0.F}),
        priority(0),
        sfmlRect(),
            size({0.F, 0.F})
{
                 
}

sgf::Color3D sgf::Rectangle::getColor() const
{
	return this->color;
}

sgf::Vector2D sgf::Rectangle::getPosition() const
{
	return this->position;
}

int sgf::Rectangle::getPriority() const
{
	return this->priority;
}

sgf::Vector2D sgf::Rectangle::getSize() const
{
	return this->size;
}

float sgf::Rectangle::getHeight() const
{
    return this->getSize().y;
}

float sgf::Rectangle::getWidth() const
{
    return this->getSize().x;
}

float sgf::Rectangle::getX() const
{
    return this->getPosition().x;
}
float sgf::Rectangle::getY() const
{
    return this->getPosition().y;
}

void sgf::Rectangle::onKeyboardInput(sgf::Unicode data) const
{
    if(this->keyboardListener != nullptr)
        keyboardListener(data, this->keyboardPayload);
}

void sgf::Rectangle::onMouseInput(sgf::MouseEvent event, sgf::Vector2D position) const
{
    if(this->mouseListener != nullptr)
        mouseListener(event, position, this->mousePayload);
}

sgf::Rectangle& sgf::Rectangle::setColor(sgf::Color3D color)
{
	this->color = color;
	this->sfmlRect.setFillColor(sf::Color(color.r, color.g, color.b));
	return *this;
}

sgf::Rectangle& sgf::Rectangle::setKeyboardListener(sgf::KeyboardListener callback, void* payload)
{
    this->keyboardListener = callback;
    this->keyboardPayload  = payload;
    return *this;
}

sgf::Rectangle& sgf::Rectangle::setMouseListener(sgf::MouseListener callback, void* payload)
{
    this->mouseListener = callback;
    this->mousePayload  = payload;
    return *this;
}

sgf::Rectangle& sgf::Rectangle::setPosition(sgf::Vector2D position)
{
	this->position = position;
	this->sfmlRect.setPosition(sf::Vector2f(position.x, position.y));
	return *this;
}

sgf::Rectangle& sgf::Rectangle::setPriority(int priority)
{
	this->priority = priority;
	return *this;
}

sgf::Rectangle& sgf::Rectangle::setSize(sgf::Vector2D size)
{
	this->size = size;
	this->sfmlRect.setSize(sf::Vector2f(size.x, size.y));
	return *this;
}
