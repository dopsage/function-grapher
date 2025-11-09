
/********** SIMPLE GUI FRAMEWORK TYPES MODULE **********/

#ifndef _TYPES_HPP
#define _TYPES_HPP

namespace sgf
{
    class                                 Canvas;
    class                                 InputManager;
    class                                 Rectangle;
    struct                                Vector2D { float x, y; };
    typedef unsigned char                 Byte;
    struct                                Color3D  { Byte r, g, b; };
    typedef sf::Uint32                    Unicode;
    typedef void                        (*KeyboardListener)(Unicode data);
    typedef unsigned long long            Milliseconds;
    typedef void                        (*MouseListener)(bool isDown, Vector2D position);
    typedef std::vector<const Rectangle*> RectangleTuple;
}

#endif
