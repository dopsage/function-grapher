
#include "SGF/InputManager.hpp"

sgf::InputManager::InputManager()
{
    
}

void sgf::InputManager::pushKeyboardData(sgf::Unicode data)
{
    if(this->keyboardReceiver != nullptr)
        keyboardReceiver->onKeyboardInput(data);
}

void sgf::InputManager::pushMouseData(bool isDown, sgf::Vector2D position)
{
    // Find out which rectangles shall receive the mouse event, base it on coordinates and priorities.
    for(const sgf::Rectangle* rect : *rectangles)
        rect->onMouseInput(isDown, position);
}

sgf::InputManager& sgf::InputManager::setKeyboardReceiver(const sgf::Rectangle* rectangle)
{
    this->keyboardReceiver = rectangle;
    return *this;
}

sgf::InputManager& sgf::InputManager::setRectangleSource(const sgf::RectangleTuple* rectangles)
{
    this->rectangles = rectangles;
    return *this;
}
