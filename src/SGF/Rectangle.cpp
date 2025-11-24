
#include "SGF/Rectangle.hpp"

sgf::Rectangle::Rectangle() : 
           color({0, 0, 0}),
keyboardListener(nullptr),
   mouseListener(nullptr),
            meta(nullptr),
        position({0.F, 0.F}),
        priority(0),
        sfmlRect(),
            size({0.F, 0.F}),
         visible(true)
{
                 
}

bool sgf::Rectangle::contains(sgf::Vector2D position) const
{
    return position.x >= this->position.x &&
           position.y >= this->position.y &&
           position.x <= this->position.x + this->size.x &&
           position.y <= this->position.y + this->size.y;
}

sgf::Color3D sgf::Rectangle::getColor() const
{
	return this->color;
}

int sgf::Rectangle::getID() const
{
    return this->id;
}

void* sgf::Rectangle::getMeta()
{
    return this->meta;
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

bool sgf::Rectangle::getVisible() const
{
    return this->visible;
}

float sgf::Rectangle::getX() const
{
    return this->getPosition().x;
}
float sgf::Rectangle::getY() const
{
    return this->getPosition().y;
}

void sgf::Rectangle::onKeyboardInput(sgf::Unicode data)
{
    if(this->visible && this->keyboardListener != nullptr)
        keyboardListener(data, this->id, this->canvas);
}

void sgf::Rectangle::onMouseInput(sgf::MouseEvent event, sgf::Vector2D position)
{
    if(this->visible && this->mouseListener != nullptr)
        mouseListener(event, position, this->id, this->canvas);
}

sgf::Rectangle& sgf::Rectangle::setColor(sgf::Color3D color)
{
	this->color = color;
	this->sfmlRect.setFillColor(sf::Color(color.r, color.g, color.b));
	return *this;
}

sgf::Rectangle& sgf::Rectangle::setKeyboardListener(sgf::KeyboardListener callback)
{
    this->keyboardListener = callback;
    return *this;
}

sgf::Rectangle& sgf::Rectangle::setMouseListener(sgf::MouseListener callback)
{
    this->mouseListener = callback;
    return *this;
}

sgf::Rectangle& sgf::Rectangle::setMeta(void* meta)
{
    this->meta = meta;
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

sgf::Rectangle& sgf::Rectangle::setVisible(bool visible)
{
    this->visible = visible;
    return *this;
}

