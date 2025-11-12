
/********** SIMPLE GUI FRAMEWORK CANVAS MODULE **********/

#ifndef _CANVAS_HPP
#define _CANVAS_HPP

#include <chrono>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SGF/InputManager.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

class Canvas final
{
private:
    Milliseconds     constructionTime;
    float            drawingFrequency;
    Milliseconds     frameDuration;
    Milliseconds     getEpochTime() const;
    InputManager     inputManager;
    bool             isAlive;
    Milliseconds     lastDrawTime;
    Vector2D         position;
    RectangleTuple   rectangles;
    sf::RenderWindow sfmlWindow;
    Vector2D         size;
    const char*      title;

public:
    Canvas();
    void              add(const Rectangle& rect);
    bool              alive() const;
    float             getDrawingFrequency() const;
    float 			  getHeight() const;
    float 			  getWidth() const;
    Vector2D          getPosition() const;
    Vector2D          getSize() const;
    const char*       getTitle() const;
    Milliseconds      getElapsedTime() const;
    InputManager&     getInputManager();
    float 			  getX() const;
    float 			  getY() const;
    void              kill();
    bool              tick();
    bool              remove(const Rectangle& rect);
    Canvas&           setDrawingFrequency(float drawingFrequency);
    Canvas&           setPosition(Vector2D position);
    Canvas&           setSize(Vector2D size);
    Canvas&           setTitle(const char* title);
};

}

#endif
