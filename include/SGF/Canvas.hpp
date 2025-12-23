
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
 * way that makes the framework intuitive and primitive (but simple). */
class Canvas final
{
private:
    Milliseconds             constructionTime;
    float                    drawingFrequency;
    static const std::string fontFile;
    Milliseconds             tickDuration;
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
    int                      tickIndex;
    const char*              title;

public:
    Canvas();
    void            add(Rectangle& rect);
    bool            alive() const;
    Milliseconds    getElapsedTime() const;
    float 		    getHeight() const;
    InputParser&    getInputParser();
    Vector2D        getPosition() const;
    Rectangle*      getRectangle(int id);
    Vector2D        getSize() const;
    Milliseconds    getTickDuration() const;
    int             getTickIndex() const;
    const char*     getTitle() const;
    float 		    getWidth() const;
    float 		    getX() const;
    float 		    getY() const;
    void            kill();
    void            remove(Rectangle& rect);
    void            setPosition(Vector2D position);
    void            setSize(Vector2D size);
    void            setTickDuration(Milliseconds duration);
    void            setTitle(const char* title);
    bool            tick();
};

}

#endif
