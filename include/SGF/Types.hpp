
/********** SIMPLE GUI FRAMEWORK TYPES MODULE **********/

#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <string>

namespace sgf
{
    typedef unsigned char Byte;
    typedef unsigned long long Milliseconds;
    typedef const std::vector<std::pair<int, int>> RangeVector;
    
    class Button;
    class Canvas;
    class InputParser;
    class Rectangle;
    class ScrollView;
    class Slider;
    class TextInput;
    class VList;
    
    enum class InputFilter
    {
        // NOTICE: Ranges are defined in unicode
        
        BYTE,   // Visible characters in the first byte of unicode table
        MATH    // Simple math expressions
    };
    const RangeVector IF_BYTE =
    {
        {0x0021, 0x007E},
        {0x00A1, 0x00FF}
    };
    const RangeVector IF_MATH =
    {
        {0x0028, 0x002B},   // ( ) * +
        {0x0030, 0x0039},   // 0-9
        {0x002D, 0x002F},   // - . /
        {0x003D, 0x003D},   // =
        {0x0041, 0x005A},   // A-Z
        {0x005E, 0x005E},   // ^
        {0x0061, 0x007A}    // a-z
    };
    
    enum class MouseEvent
    {
        DOWN,
        MOVE,
        UP
    };
    
    struct Vector2D
    {
        float x;
        float y;
    };
    
    struct Color3D 
    {
        Byte r;
        Byte g;
        Byte b;
    };
    
    struct TextProperties
    {
        // Variable
        Color3D     color;          // Uniform color
        std::string content;        // Contained text data
        bool        refreshFlag;    // If set, canvas updates the SFML text with the properties and resets the flag
        int         size;           // Character size in pixels
        
        // Read-only
        int         width;          // Width of the text content in pixels
    };
    
    typedef void (*ButtonListener)      (int rectangleId, Canvas* canvasPtr);
    typedef void (*KeyboardListener)    (int data, int rectangleId, Canvas* canvasPtr);
    typedef void (*MouseListener)       (MouseEvent event, Vector2D position, int rectangleId, Canvas* canvasPtr);
    typedef void (*SliderListener)      (float value, int rectangleId, Canvas* canvasPtr);
    typedef void (*TextInputListener)   (std::string content, int rectangleId, sgf::Canvas* canvasPtr);
}

#endif
