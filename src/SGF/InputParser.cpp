
#include "SGF/InputParser.hpp"

const sgf::Rectangle* sgf::InputParser::getHoveredRectangle(const sgf::Vector2D& position) const
{
    const sgf::Rectangle* receiver = nullptr;
    for(const sgf::Rectangle* rect : *rectangles)
        if(receiver == nullptr ||
          (position.x >= rect->getX() &&
           position.y >= rect->getY() &&
           position.x <= rect->getX() + rect->getWidth()  &&
           position.y <= rect->getY() + rect->getHeight() &&
           rect->getPriority() >= receiver->getPriority()))
            receiver = rect;
    return receiver;
}

sgf::InputParser::InputParser() :
mouseReceiver(nullptr)
{
    
}

void sgf::InputParser::parseSfmlEvent(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::TextEntered:
            keyboardReceiver->onKeyboardInput(event.text.unicode);
            break;
        /* It allows an event receiver to capture the mouse; so while left mouse
         * button is held, events still arrive to the receiver despite the mouse
         * not hovering it. */
        case sf::Event::MouseButtonPressed:
            if(event.mouseButton.button == sf::Mouse::Button::Left)
            {
                sgf::Vector2D position = { event.mouseButton.x, event.mouseButton.y };
                mouseReceiver = getHoveredRectangle(position);
                mouseReceiver->onMouseInput(sgf::MouseEvent::DOWN, position);
            }
            break;
        case sf::Event::MouseMoved:
            if(mouseReceiver != nullptr)
                mouseReceiver->onMouseInput(sgf::MouseEvent::MOVE, { event.mouseMove.x, event.mouseMove.y });
            break;
        case sf::Event::MouseButtonReleased:
            if(mouseReceiver != nullptr)
            {
                mouseReceiver->onMouseInput(sgf::MouseEvent::UP, { event.mouseButton.x, event.mouseButton.y });
                mouseReceiver = nullptr;
            }
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
