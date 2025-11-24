
#include "SGF/InputParser.hpp"

sgf::Rectangle* sgf::InputParser::getHoveredRectangle(const sgf::Vector2D& position) const
{
    sgf::Rectangle* receiver = nullptr;
    for(sgf::Rectangle* rect : *rectangles)
        if(receiver == nullptr || (rect->getVisible() && rect->contains(position) && rect->getPriority() >= receiver->getPriority()))
            receiver = rect;
    return receiver;
}

sgf::InputParser::InputParser() :
keyboardReceiver(nullptr),
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
        
        /* These allows an event receiver to capture the mouse; so while left mouse
         * button is held, events still arrive to the receiver despite the mouse
         * not hovering it. */
        case sf::Event::MouseButtonPressed:
            if(event.mouseButton.button == sf::Mouse::Button::Left)
            {
                sgf::Vector2D position = { (float)event.mouseButton.x, (float)event.mouseButton.y };
                mouseReceiver = getHoveredRectangle(position);
                mouseReceiver->onMouseInput(sgf::MouseEvent::DOWN, position);
            }
            break;
        case sf::Event::MouseMoved:
            if(mouseReceiver != nullptr)
                mouseReceiver->onMouseInput(sgf::MouseEvent::MOVE, { (float)event.mouseMove.x, (float)event.mouseMove.y });
            break;
        case sf::Event::MouseButtonReleased:
            if(mouseReceiver != nullptr)
            {
                mouseReceiver->onMouseInput(sgf::MouseEvent::UP, { (float)event.mouseButton.x, (float)event.mouseButton.y });
                mouseReceiver = nullptr;
            }
            break;
    }
}

sgf::InputParser& sgf::InputParser::setKeyboardReceiver(sgf::Rectangle* rectangle)
{
    this->keyboardReceiver = rectangle;
    return *this;
}

sgf::InputParser& sgf::InputParser::setRectangleSource(sgf::RectangleVector* rectangles)
{
    this->rectangles = rectangles;
    return *this;
}
