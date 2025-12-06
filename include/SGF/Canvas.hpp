
/********** SIMPLE GUI FRAMEWORK CANVAS MODULE **********/

#ifndef _CANVAS_HPP
#define _CANVAS_HPP

#include <chrono>
#include <deque>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SGF/InputParser.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Core of SGF, it facilitates rendering of a window and its contents in form of
 * simple rectangular areas (Rectangle instances) by wrapping SFML features in a
 * way that makes the framework intuitive and primitive (but simple).  */
class Canvas final
{
private:
    Milliseconds             constructionTime;
    float                    drawingFrequency;
    static const std::string fontFile;
    Milliseconds             frameDuration;
    Milliseconds             getEpochTime() const;
    InputParser              inputParser;
    bool                     isAlive;
    Milliseconds             lastDrawTime;
    Vector2D                 position;
    RectangleVector          rectangles;
    int                      rectCount;
    sf::Font                 sfmlFont;
    sf::RenderWindow         sfmlWindow;
    Vector2D                 size;
    std::deque<sf::Text>     texts;
    const char*              title;

public:
    Canvas();
    void         add(Rectangle& rect);
    bool         alive() const;
    float        getDrawingFrequency() const;
    float 		 getHeight() const;
    float 		 getWidth() const;
    Vector2D     getPosition() const;
    Vector2D     getSize() const;
    const char*  getTitle() const;
    Milliseconds getElapsedTime() const;
    InputParser& getInputParser();
    Rectangle*   getRectangle(int id);
    float 		 getX() const;
    float 		 getY() const;
    void         kill();
    bool         tick();
    Canvas&      setDrawingFrequency(float drawingFrequency);
    Canvas&      setPosition(Vector2D position);
    Canvas&      setSize(Vector2D size);
    Canvas&      setTitle(const char* title);
};

}

#endif
