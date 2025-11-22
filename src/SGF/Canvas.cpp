
#include "SGF/Canvas.hpp"

sgf::Milliseconds sgf::Canvas::getEpochTime() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();
}

sgf::Canvas::Canvas() :
constructionTime(getEpochTime()),
     inputParser(),
         isAlive(true),
    lastDrawTime(0),
      rectangles(),
      sfmlWindow(sf::VideoMode(1, 1), "", sf::Style::Titlebar | sf::Style::Close)
{
    this->inputParser.setRectangleSource(&rectangles);
    this->setDrawingFrequency(60.F);
    this->setPosition({0.F, 0.F});
    this->setSize({128.F, 128.F});
    this->setTitle("Simple GUI Framework Application");
    
    sfmlWindow.setKeyRepeatEnabled(false);
}

void sgf::Canvas::add(const Rectangle& rect)
{
    /* After addition to rectangles tuple, remain it sorted according to priority
     * from smallest to highest. Order for later drawing in case of equal priorities
     * is fully preserved. */ 
    for(int index = 0; index < rectangles.size(); index++)
        if(rectangles.at(index)->getPriority() > rect.getPriority())
        {
            rectangles.insert(rectangles.begin() + index, &rect);
            return;
        }
    rectangles.push_back(&rect);
}

bool sgf::Canvas::alive() const
{
    return this->isAlive;
}

float sgf::Canvas::getDrawingFrequency() const
{
    return this->drawingFrequency;
}

float sgf::Canvas::getHeight() const
{
	return this->size.y;
}

float sgf::Canvas::getWidth() const
{
	return this->size.x;
}

sgf::Vector2D sgf::Canvas::getPosition() const
{
    return this->position;
}

sgf::Vector2D sgf::Canvas::getSize() const
{
    return this->size;
}

const char* sgf::Canvas::getTitle() const
{
    return this->title;
}

sgf::Milliseconds sgf::Canvas::getElapsedTime() const
{
    return getEpochTime() - this->constructionTime;
}

sgf::InputParser& sgf::Canvas::getInputParser()
{
    return this->inputParser;
}

float sgf::Canvas::getX() const
{
	return this->position.x;
}

float sgf::Canvas::getY() const
{
	return this->position.y;
}

void sgf::Canvas::kill()
{
	this->isAlive = false;
}

bool sgf::Canvas::tick()
{
    if(!isAlive) return false;
    
    sf::Event event;
    while (sfmlWindow.pollEvent(event))
        switch(event.type)
        {
            case sf::Event::Closed:
                isAlive = false;
                sfmlWindow.close();
                return false;
            /* The rest of events are passed to the input parser, which interprets
             * them in context of all rectangles */
            default:
                inputParser.parseSfmlEvent(event);
                break;
        }
    
    sgf::Milliseconds elapsedTime = getElapsedTime();
    if(elapsedTime - lastDrawTime > frameDuration)
    {
        sfmlWindow.clear();
        
        // Draw rectangles by exploiting their one-way magic of friendship
        for(const Rectangle* rect : rectangles)
            sfmlWindow.draw(rect->sfmlRect);
        
        sfmlWindow.display();
        
        lastDrawTime = elapsedTime;
        return true;
    }
    
    return false;
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

sgf::Canvas& sgf::Canvas::setDrawingFrequency(float drawingFrequency)
{
    this->drawingFrequency = drawingFrequency;
    this->frameDuration    = (Milliseconds)(1000.F / drawingFrequency);
    return *this;
}

sgf::Canvas& sgf::Canvas::setPosition(sgf::Vector2D position)
{
    this->position = position;
    this->sfmlWindow.setPosition(sf::Vector2i(position.x, position.y));
    return *this;
}

sgf::Canvas& sgf::Canvas::setSize(Vector2D size)
{
    this->size = size;
    this->sfmlWindow.setSize(sf::Vector2u(size.x, size.y));
    this->sfmlWindow.setView(sf::View(sf::FloatRect(0.F, 0.F, size.x, size.y)));
    return *this;
}

sgf::Canvas& sgf::Canvas::setTitle(const char* title)
{
    this->title = title;
    this->sfmlWindow.setTitle(sf::String(title));
    return *this;
}
