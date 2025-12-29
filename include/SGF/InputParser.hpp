
/********** SIMPLE GUI FRAMEWORK INPUT PARSER MODULE **********/

#ifndef _INPUTPARSER_HPP
#define _INPUTPARSER_HPP

#include "SFML/Graphics.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Defines how rectangles contained in a specified source vector are receiving SFML
 * keyboard and mouse events. The class also introduces lots of custom events, that
 * are pretty useful. */
class InputParser final
{
private:
    Rectangle*      getHoveredRectangle(const Vector2D& position) const;
    Rectangle*      keyboardReceiver;
    Rectangle*      mouseReceiver;
    RectangleDeque* rectangles;

public:
    InputParser();
    bool         isKeyboardFree() const;
    void         parseSfmlEvent(const sf::Event& event);
    InputParser& setKeyboardReceiver(Rectangle* rectangle);
    InputParser& setRectangleSource(std::deque<Rectangle*>* rectangles);
};

}

#endif
