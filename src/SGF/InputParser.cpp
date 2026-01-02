
#include "SGF/InputParser.hpp"

using namespace sgf;

Rectangle* InputParser::getHoveredRectanglePtr(Vector2D position)
{
    Rectangle* hovered = nullptr;
    for(Rectangle* r : *rectanglesSourcePtr)
        if(  r->isVisible()         &&
             r->contains(position)  &&
            (hovered == nullptr || r->getPriority() >= hovered->getPriority()))
             hovered = r;

    return hovered;
}

InputParser::   InputParser() :
                mouseReceiverPtr(nullptr)
{
    setKeyboardReceiverPtr(nullptr);
    setRectanglesSourcePtr(nullptr);
}

bool InputParser::isKeyboardFree() const
{
    return (keyboardReceiverPtr == nullptr);
}

void InputParser::parseSfmlEvent(const sf::Event& event)
{
    switch(event.type)
    {
		/* KeyPressed event provides all keys that are missing in TextEntered event.
		 * In order to distinct one from another, first mentioned always passes negative
		 * corresponding to some key code, while the second passes just the unicode
		 * character code. Thus negatives shall be used for control, and positives for keys. */
		case sf::Event::KeyPressed:
        case sf::Event::TextEntered:
        {
			if(keyboardReceiverPtr != nullptr)
				keyboardReceiverPtr->onKeyboardInput(event.type == sf::Event::KeyPressed ?
                (-1 * (int)event.key.code) : (event.text.unicode));
            break;
        }
        
        /* These allows an event receiver to capture the mouse; so while left mouse
         * button is held, events still arrive to the receiver despite the mouse
         * not hovering it. */
        case sf::Event::MouseButtonPressed:
        {
            if(event.mouseButton.button == sf::Mouse::Button::Left)
            {
                Vector2D position   = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                mouseReceiverPtr    = getHoveredRectanglePtr(position);
                
                if(mouseReceiverPtr != nullptr)
                    mouseReceiverPtr->onMouseInput(MouseEvent::DOWN, position);
            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            if(mouseReceiverPtr == nullptr)
            {
                Vector2D position       = {(float)event.mouseMove.x, (float)event.mouseMove.y};
                Rectangle* receiverPtr  = getHoveredRectanglePtr(position);
                
                if(receiverPtr != nullptr)
                    receiverPtr->onMouseInput(MouseEvent::MOVE, position);
            }
            else
            {
                mouseReceiverPtr->onMouseInput(MouseEvent::MOVE, {
                    (float)event.mouseMove.x,
                    (float)event.mouseMove.y
                });
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if(event.mouseButton.button == sf::Mouse::Button::Left && mouseReceiverPtr != nullptr)
            {
                mouseReceiverPtr->onMouseInput(MouseEvent::UP, {
                    (float)event.mouseButton.x,
                    (float)event.mouseButton.y
                });
                mouseReceiverPtr = nullptr;
            }
            break;
        }
    }
}

void InputParser::setKeyboardReceiverPtr(Rectangle* receiverPtr)
{
    keyboardReceiverPtr = receiverPtr;
}

void InputParser::setRectanglesSourcePtr(std::vector<Rectangle*>* sourcePtr)
{
    rectanglesSourcePtr = sourcePtr;
}
