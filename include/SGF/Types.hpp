
/********** SIMPLE GUI FRAMEWORK TYPES MODULE **********/

#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <string>

namespace sgf
{
    typedef unsigned char Byte;
    typedef unsigned long long Milliseconds;
    
    class Button;
    class Canvas;
    class InputParser;
    class Rectangle;
    class Slider;
    class TextInput;
    enum class MouseEvent { DOWN, MOVE, UP };
    struct Vector2D { float x, y; };
    struct Color3D  { Byte r, g, b; };
    struct TextProperties { Color3D color; std::string content; unsigned int size; };
    
    typedef std::vector<Rectangle*> RectangleVector;
    typedef void (*ButtonListener)(int id, Canvas* canvas);
    typedef void (*KeyboardListener)(int data, int id, Canvas* canvas);
    typedef void (*MouseListener)(MouseEvent event, Vector2D position, int id, Canvas* canvas);
    typedef void (*SliderListener)(float value, int id, Canvas* canvas);
}

#endif
