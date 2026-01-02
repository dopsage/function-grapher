
#include "SGF/Rectangle.hpp"

using namespace sgf;

Rectangle:: Rectangle() :
            canvasPtr(nullptr),
            id(-1),
            sfmlRect(),
            textPtr(nullptr),
            usingText(false)
{
    setColor({0,0,0});              // color
    setKeyboardListener(nullptr);   // keyboardListener
    setMouseListener(nullptr);      // mouseListener
    setMetaPtr(nullptr);            // metaPtr
    setPosition({0.0f,0.0f});       // position
    setPriority(0);                 // priority
    setSize({0.0f,0.0f});           // size
    setText(nullptr);               // textPtr
    setVisible(true);               // visible
}

Rectangle::~Rectangle()
{
    // Not implemented by default
}

bool Rectangle::contains(Vector2D position) const
{
    return position.x >= this->position.x                   &&
           position.y >= this->position.y                   &&
           position.x <= this->position.x + this->size.x    &&
           position.y <= this->position.y + this->size.y;
}

void Rectangle::copy(Rectangle* other)
{
    setColor            (other->getColor());
    setKeyboardListener (other->getKeyboardListener());
    setMouseListener    (other->getMouseListener());
    setMetaPtr          (other->getMetaPtr());
    setPosition         (other->getPosition());
    setPriority         (other->getPriority());
    setSize             (other->getSize());
    setText             (other->getText());
    setVisible          (other->isVisible());
}

Canvas* Rectangle::getCanvasPtr()
{
    return canvasPtr;
}

Color3D Rectangle::getColor() const
{
	return color;
}

float Rectangle::getHeight() const
{
    return size.y;
}

int Rectangle::getId() const
{
    return id;
}

KeyboardListener Rectangle::getKeyboardListener() const
{
    return keyboardListener;
}

void* Rectangle::getMetaPtr()
{
    return metaPtr;
}

MouseListener Rectangle::getMouseListener() const
{
    return mouseListener;
}

Vector2D Rectangle::getPosition() const
{
	return position;
}

int Rectangle::getPriority() const
{
	return priority;
}

Vector2D Rectangle::getSize() const
{
	return size;
}

TextProperties* Rectangle::getText()
{
    return textPtr;
}

float Rectangle::getWidth() const
{
    return size.x;
}

float Rectangle::getX() const
{
    return position.x;
}
float Rectangle::getY() const
{
    return position.y;
}

bool Rectangle::isUsingText() const
{
    return usingText;
}

bool Rectangle::isVisible() const
{
    return visible;
}

void Rectangle::onKeyboardInput(int data)
{
    if(visible && keyboardListener != nullptr)
        keyboardListener(data, id, canvasPtr);
}

void Rectangle::onMouseInput(MouseEvent event, Vector2D position)
{
    if(visible && mouseListener != nullptr)
        mouseListener(event, position, id, canvasPtr);
}

void Rectangle::onAdd()
{
    // Not implemented by default
}

void Rectangle::onRemove()
{
    // Not implemented by default
}

void Rectangle::onTick(int tickCount)
{
    // Not implemented by default
}

void Rectangle::setColor(Color3D color)
{
	this->color = color;
    
	sfmlRect.setFillColor(sf::Color(color.r, color.g, color.b));
}

void Rectangle::setKeyboardListener(KeyboardListener callback)
{
    keyboardListener = callback;
}

void Rectangle::setMouseListener(MouseListener callback)
{
    mouseListener = callback;
}

void Rectangle::setMetaPtr(void* ptr)
{
    metaPtr = ptr;
}

void Rectangle::setPosition(Vector2D position)
{
	this->position = position;
    
	sfmlRect.setPosition(sf::Vector2f(position.x, position.y));
    
    // If rectangle uses text, it needs its position updated. Canvas does that on refresh
    if(usingText)
        textPtr->refreshFlag = true;
}

void Rectangle::setPriority(int priority)
{
	this->priority = priority;
}

void Rectangle::setSize(Vector2D size)
{
	this->size = size;
    
	sfmlRect.setSize(sf::Vector2f(size.x, size.y));
}

void Rectangle::setText(TextProperties* properties)
{
    if(properties == nullptr)
    {
        usingText = false;
        return;
    }
    
    // Provided properties are valid, update fields and mark the SFML text for refresh
    textPtr                 = properties;
    usingText               = true;
    textPtr->refreshFlag    = true;
}

void Rectangle::setVisible(bool visible)
{
    this->visible = visible;
}
