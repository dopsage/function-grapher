
/********** SIMPLE GUI FRAMEWORK INPUT PARSER MODULE **********/

#ifndef _INPUTPARSER_HPP
#define _INPUTPARSER_HPP

#include "SFML/Graphics.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Defines how rectangles contained in a specified source tuple are receiving SFML keyboard and mouse
 * events. The class also introduces lots of custom events, that are pretty useful. */
class InputParser final
{
private:
    const Rectangle*      getHoveredRectangle(const Vector2D& position) const;
    const Rectangle*      keyboardReceiver;
    const Rectangle*      mouseReceiver;
    const RectangleTuple* rectangles;

public:
    InputParser();
    void         parseSfmlEvent(const sf::Event& event);
    InputParser& setKeyboardReceiver(const Rectangle* rectangle);
    InputParser& setRectangleSource(const RectangleTuple* rectangles);
};

}

#endif
