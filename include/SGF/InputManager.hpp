
/********** SIMPLE GUI FRAMEWORK EVENT MANAGER MODULE **********/

// note: this class justs activates callbacks of rectangles in a tuple, given created events!

#ifndef _INPUTMANAGER_HPP
#define _INPUTMANAGER_HPP

#include "SFML/Graphics.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

class InputManager final
{
private:
    const Rectangle*      keyboardReceiver;
    const RectangleTuple* rectangles;

 // make him offer realtime mouse data, or make something so it can push mouse data on ouse move (dont let canvas do input work!)

public:
    InputManager();
    void          pushKeyboardData(Unicode data);
    void          pushMouseData(bool isDown, Vector2D position);
    InputManager& setKeyboardReceiver(const Rectangle* rectangle);
    InputManager& setRectangleSource(const RectangleTuple* rectangles);
};

}

#endif
