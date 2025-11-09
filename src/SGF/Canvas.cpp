
#include "SGF/Canvas.hpp"

sgf::Milliseconds sgf::Canvas::getEpochTime() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();
}

sgf::Canvas::Canvas() :
constructionTime(getEpochTime()),
         isAlive(true),
    lastDrawTime(0),
      rectangles(),
      sfmlWindow(sf::VideoMode(1, 1), "", sf::Style::Titlebar | sf::Style::Close)
{
    this->inputManager.setRectangleSource(&rectangles);
    this->setDrawingFrequency(60.F);
    this->setPosition({0.F, 0.F});
    this->setSize({128.F, 128.F});
    this->setTitle("Simple GUI Framework Application");
    
    sfmlWindow.setKeyRepeatEnabled(false);
}

// TODO: Better describe process of this method ...
void sgf::Canvas::add(const Rectangle& rect)
{
    /* ALGORITHM.
     * Rectangles array remains sorted according to priority, from smallest to highest.
     * Order for later drawing in equal priorities is also preserved. */ 
    for(int index = 0; index < rectangles.size(); index++)
        if(rectangles.at(index)->priority > rect.priority)
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

float sgf::Canvas::getDrawingFrequency() const
{
    return this->drawingFrequency;
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

sgf::InputManager& sgf::Canvas::getInputManager()
{
    return this->inputManager;
}

void sgf::Canvas::kill()
{
	this->isAlive = false;
}

// TODO: Better describe process of this method ...
bool sgf::Canvas::tick()
{
    if(!isAlive) return false;
    
    // Pass data for IM to work on...
    sf::Event event;
    while (sfmlWindow.pollEvent(event))
        switch(event.type)
        {
            case sf::Event::Closed:
                isAlive = false;
                sfmlWindow.close();
                return false;
            
            case sf::Event::TextEntered:
                inputManager.pushKeyboardData(event.text.unicode);
                break;
            
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Button::Left)
                    inputManager.pushMouseData(true, { event.mouseButton.x, event.mouseButton.y });
                break;
                
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Button::Left)
                    inputManager.pushMouseData(false, { event.mouseButton.x, event.mouseButton.y });
                break;
        }
    
    sgf::Milliseconds elapsedTime = getElapsedTime();
    if(elapsedTime - lastDrawTime > frameDuration)
    {
        sfmlWindow.clear();
        
        // Draw rectangles...
        for(const Rectangle* rect : rectangles)
            sfmlWindow.draw(rect->sfmlRect);
        
        sfmlWindow.display();
        
        lastDrawTime = elapsedTime;
        return true;
    }
    
    return false;
}

// TODO: Better describe process of this method ...
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
