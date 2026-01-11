
/********** SIMPLE GUI FRAMEWORK CONTEXT MODULE **********/

#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP

#include <cmath>

#include "SFML/Graphics.hpp"
#include "SGF/Types.hpp"

//#include "SGF/Canvas.hpp"

namespace sgf
{

typedef void (*ContextListener) (Context* contextPtr, Rectangle* instancePtr, Canvas* canvasPtr);

/* DESC */
class Context final
{
    // Allow canvas assign itself in purpose of drawing on it
    friend class Canvas;

private:
    sf::RenderWindow* sfmlWindowPtr;
    
public:
    Context();
    
    void line(Vector2D start, Vector2D end, Color3D color, int thickness);
};

}

#endif
