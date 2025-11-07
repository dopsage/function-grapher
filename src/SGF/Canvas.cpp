
#include "SGF/Canvas.hpp"

sgf::Milliseconds sgf::Canvas::getEpochTime() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();
}

sgf::Canvas::Canvas(uint width, uint height, const char* title, float drawingFrequency)
: error(Error::NONE), height(height), isAlive(true), lastDrawTime(0),
sfmlWindow(sf::VideoMode(width, height), title), width(width)
{
    if(drawingFrequency <= 0.F)
    {
        error = Error::INVALID_PARAMETER;
        return;
    }
    
    this->constructionTime = getEpochTime();
    this->frameDuration    = (Milliseconds)(1000.F / drawingFrequency);
    this->rectangles       = std::vector<const sgf::Rectangle*>();
}

void sgf::Canvas::add(const Rectangle& rect)
{
    /* ALGORITHM.
     * Rectangles array remains sorted according to priority, from smallest to highest.
     * Order for later drawing in equal priorities is also preserved. */ 
    for(int index = 0; index < rectangles.size(); index++)
        if(rectangles.at(index)->getPriority() > rect.getPriority())
        {
            rectangles.insert(rectangles.begin() + index, &rect);
            return;
        }
  
    // There is no higher priority ...
    rectangles.push_back(&rect);
}

bool sgf::Canvas::alive() const
{
    return this->isAlive;
}

bool sgf::Canvas::draw()
{
    if(!isAlive) return false;
    
    sf::Event event;
    while (sfmlWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            isAlive = false;
            sfmlWindow.close();
            
            return false;
        }
    }
    
    sgf::Milliseconds elapsedTime = getElapsedTime();
    if(elapsedTime - lastDrawTime > frameDuration)
    {
        sfmlWindow.clear();
        
        // Draw rectangles...
        for(const Rectangle* rect : rectangles)
            sfmlWindow.draw(rect->getSfmlRect());
        
        sfmlWindow.display();
        
        lastDrawTime = elapsedTime;
        return true;
    }
    
    return false;
}

sgf::Milliseconds sgf::Canvas::getElapsedTime() const
{
    return getEpochTime() - this->constructionTime;
}

sgf::Error sgf::Canvas::getError() const
{
    return this->error;
}

const sf::RenderWindow& sgf::Canvas::getSfmlWindow() const
{
    return this->sfmlWindow;
}

void sgf::Canvas::kill()
{
	this->isAlive = false;
}

bool sgf::Canvas::remove(const Rectangle& rect)
{
    // Remove if there is such rectangle added.
    for(int index = 0; index < rectangles.size(); index++)
        if(rectangles.at(index) == &rect)
        {
            rectangles.erase(rectangles.begin() + index);
            return true;
        }
    
    return false;
}
