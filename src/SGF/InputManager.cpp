
#include "SGF/InputManager.hpp"

sgf::InputManager::InputManager() :
lastMouseReceiver(nullptr)
{
    
}

void sgf::InputManager::pushKeyboardData(sgf::Unicode data)
{
    if(this->keyboardReceiver != nullptr)
        keyboardReceiver->onKeyboardInput(data);
}

void sgf::InputManager::pushMouseData(sgf::MouseEvent event, sgf::Vector2D position)
{
    if(rectangles == nullptr) return;
    
    // Find out which rectangle shall receive the mouse data, take rectangle priorities into account.
    const sgf::Rectangle* receiver = nullptr;
    for(const sgf::Rectangle* rect : *rectangles)
        if(receiver == nullptr ||
          (position.x >= rect->getX() &&
           position.y >= rect->getY() &&
           position.x <= rect->getX() + rect->getWidth()  &&
           position.y <= rect->getY() + rect->getHeight() &&
           rect->getPriority() >= receiver->getPriority()))
            receiver = rect;
    
    // If mouse exited area of the previous rectangle, inform it about that by simulating mouse up event.
    if(lastMouseReceiver != nullptr && receiver != lastMouseReceiver)
        lastMouseReceiver->onMouseInput(sgf::MouseEvent::UP, position);
    
    // If some rectangle was found under the mouse coordinates, feed him the event data.
    if(receiver != nullptr)
    {
        receiver->onMouseInput(event, position);
        lastMouseReceiver = receiver;
    }
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
