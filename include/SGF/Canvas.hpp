
/********** SIMPLE GUI FRAMEWORK CANVAS MODULE **********/

#ifndef _CANVAS_HPP
#define _CANVAS_HPP

#include <chrono>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SGF/Rectangle.hpp"

namespace sgf
{

typedef unsigned long long Milliseconds;

enum Error
{
    NONE = 0,
    INVALID_PARAMETER
};

class Canvas
{
private:
    Milliseconds                  constructionTime;
    Error                         error;
    Milliseconds                  frameDuration;
    uint                          height;
    bool                          isAlive;
    Milliseconds                  lastDrawTime;
    std::vector<const Rectangle*> rectangles;
    sf::RenderWindow              sfmlWindow;
    uint                          width;

    Milliseconds getEpochTime() const;

public:
    Canvas(uint width, uint height, const char* title, float drawingFrequency);
    // Saves the provided `Rectangle` instance for drawing
    void                    add(const Rectangle& rect);
    // Returns whether the canvas is still displaying stuff
    bool                    alive()          const;
    bool                    draw();
    Milliseconds            getElapsedTime() const;
    Error                   getError()       const;
    const sf::RenderWindow& getSfmlWindow()  const;
    // Makes the canvas stop displaying stuff
    void 					kill();
    bool                    remove(const Rectangle& rect);
};

}

#endif
