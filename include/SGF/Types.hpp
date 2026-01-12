
/********** SIMPLE GUI FRAMEWORK TYPES HEADER **********/

#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <cstdint>

namespace sgf
{
    /*class       Button;
    class       Canvas;
    class       Context;
    class       FunctionGrapher;
    class       FunctionParser;
    class       FunctionProperties;
    enum class  FPError;
    class       InputParser;
    class       Rectangle;
    class       ScrollView;
    class       TextInput;
    struct      TextProperties;
    class       VList;
    class       VSlider;*/
    
    typedef uint8_t     byte;
    typedef uint32_t    milliseconds;
    struct  Color3D     { byte r, g, b; };
    struct  Vector2D    { float x, y; };
}

#endif
