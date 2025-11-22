
#include "SGF/InputParser.hpp"

sgf::InputParser::InputParser() :
lastMouseReceiver(nullptr)
{
    
}

//void sgf::InputParser::parseMouseData(sgf::MouseEvent event, sgf::Vector2D position)
//{
    //if(rectangles == nullptr) return;
    
    //// Find out which rectangle shall receive the mouse data, take rectangle priorities into account.
    //const sgf::Rectangle* receiver = nullptr;
    //for(const sgf::Rectangle* rect : *rectangles)
        //if(receiver == nullptr ||
          //(position.x >= rect->getX() &&
           //position.y >= rect->getY() &&
           //position.x <= rect->getX() + rect->getWidth()  &&
           //position.y <= rect->getY() + rect->getHeight() &&
           //rect->getPriority() >= receiver->getPriority()))
            //receiver = rect;
    
    //// If mouse exited area of the previous rectangle, inform it about that by simulating mouse up event.
    //if(lastMouseReceiver != nullptr && receiver != lastMouseReceiver)
        //lastMouseReceiver->onMouseInput(sgf::MouseEvent::UP, position);
    
    //// If some rectangle was found under the mouse coordinates, feed him the event data.
    //if(receiver != nullptr)
    //{
        //receiver->onMouseInput(event, position);
        //lastMouseReceiver = receiver;
    //}
//}

void sgf::InputParser::parseSfmlEvent(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::TextEntered:
            keyboardReceiver->onKeyboardInput(event.text.unicode);
            break;
            
// TODO: Implement mouse event interpreter below
        case sf::Event::MouseButtonPressed:
            if(event.mouseButton.button == sf::Mouse::Button::Left) { }
            break;
        case sf::Event::MouseMoved:
            break;
        case sf::Event::MouseButtonReleased:
            if(event.mouseButton.button == sf::Mouse::Button::Left) { }
            break;
    }
}

sgf::InputParser& sgf::InputParser::setKeyboardReceiver(const sgf::Rectangle* rectangle)
{
    this->keyboardReceiver = rectangle;
    return *this;
}

sgf::InputParser& sgf::InputParser::setRectangleSource(const sgf::RectangleTuple* rectangles)
{
    this->rectangles = rectangles;
    return *this;
}
