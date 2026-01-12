
/********** SIMPLE GUI FRAMEWORK CONTEXT MODULE **********/

#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP

#include <cmath>

#include "SFML/Graphics.hpp"

#include "SGF/Types.hpp"

namespace sgf
{

class Canvas;

/* DESC */
class Context final
{
    // Allow canvas pass the SFML window reference in order to draw on it
    friend class Canvas;

private:
    sf::RenderWindow* sfmlWindowPtr;
    
public:
    Context();
    
    void line(Vector2D start, Vector2D end, Color3D color, int thickness);
};

}

#endif
