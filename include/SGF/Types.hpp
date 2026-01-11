
/********** SIMPLE GUI FRAMEWORK TYPES HEADER **********/

#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace sgf
{
    typedef uint8_t         byte;
    typedef uint32_t        milliseconds;

    class       Button;
    class       Canvas;
    class       Context;
    class       FunctionGrapher;
    class       FunctionProperties;
    enum class  FPError;
    class       InputParser;
    class       Rectangle;
    class       ScrollView;
    class       TextInput;
    struct      TextProperties;
    class       VList;
    class       VSlider;
    
    struct      Color3D     { byte r, g, b; };
    enum class  MouseEvent  { DOWN, MOVE, UP };
    struct      Vector2D    { float x, y; };
}

#endif
