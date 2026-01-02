
#include "SGF/Canvas.hpp"

using namespace sgf;

const std::string Canvas::RES_FONT_FILE = "./res/font/pony.ttf";

Milliseconds Canvas::getEpochTime() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();
}

Canvas::Canvas() :
        constructionTime(getEpochTime()),
        inputParser(),
        active(true),
        rectanglePtrs(),
        rectangleTexts(),
        sfmlFont(),
        sfmlWindow(sf::VideoMode(1, 1), "", sf::Style::Titlebar | sf::Style::Close),
        tickCount(0)
{
    inputParser.setRectanglesSourcePtr(&rectanglePtrs);    // Initialize input parser
    
    sfmlFont.loadFromFile(Canvas::RES_FONT_FILE);       // Load font resource
    
    setPosition({0.0f,0.0f});                           // position
    setSize({600.0F,480.0f});                           // size
    setDrawingRate(60);                                 // drawingRate
    setTitle("Simple GUI Framework Application");       // title
}

void sgf::Canvas::add(Rectangle* rectanglePtr)
{
    if(rectanglePtr == nullptr) return;
    
    /* After addition to rectangle pointers vector, remain it sorted according to
     * priority from lowest to highest. Order for later drawing in case of equal
     * priorities is preserved. */
    int index = -1;
    while(  ++index < rectanglePtrs.size() &&
            rectanglePtrs[index]->getPriority() <= rectanglePtr->getPriority());
            
    /* Only rectangle is created here. In case the rectangle declares text usage,
     * its creation is handled by the drawing loop automatically. */
    rectanglePtrs.insert(rectanglePtrs.begin() + index, rectanglePtr);
    
    // Update IDs of all rectangles to the right from the inserted one including it
    for(int i = index; i < rectanglePtrs.size(); i++)
        rectanglePtrs[i]->id = i;
    
    // Let the rectangle communicate back, and notify it about successfull addition
    rectanglePtr->canvasPtr = this;
    rectanglePtr->onAdd();
}

int Canvas::getDrawingRate() const
{
    return drawingRate;
}

Milliseconds Canvas::getElapsedTime() const
{
    return getEpochTime() - constructionTime;
}

float Canvas::getHeight() const
{
	return size.y;
}

InputParser* Canvas::getInputParser()
{
    return &inputParser;
}

Vector2D Canvas::getPosition() const
{
    return position;
}

Rectangle* Canvas::getRectanglePtr(int rectangleId)
{
    return  rectangleId > -1 && rectangleId < rectanglePtrs.size() ?
            rectanglePtrs[rectangleId] : nullptr;
}

Vector2D Canvas::getSize() const
{
    return size;
}

int Canvas::getTickCount() const
{
    return tickCount;
}

std::string Canvas::getTitle() const
{
    return title;
}

float Canvas::getWidth() const
{
	return size.x;
}

float Canvas::getX() const
{
	return position.x;
}

float Canvas::getY() const
{
	return position.y;
}

bool Canvas::isActive() const
{
    return active;
}

void Canvas::stop()
{
// TODO:    I propose removing all rectangles here in order to trigger onRemove callbacks
//          on them so they can clean up things they allocated (possibly).
    sfmlWindow.close();
	active = false;
}

void Canvas::remove(int rectangleId)
{
    Rectangle* targetPtr = getRectanglePtr(rectangleId);
    if(targetPtr == nullptr) return;
    
    // Notify the target about its removal
    targetPtr->onRemove();

    /* Destroy the target rectangle, together with its associated SFML text instance
     * if it declared its usage to this point. */
    rectanglePtrs.erase(rectanglePtrs.begin() + rectangleId);
    if(targetPtr->isUsingText())
        rectangleTexts.erase(rectangleId);
    
    // Update IDs of all rectangles to the right from the already erased one
    for(int i = rectangleId; i < rectanglePtrs.size(); i++)
        rectanglePtrs[i]->id = i;
}

void Canvas::setDrawingRate(int amount)
{
    drawingRate = amount;
    
    sfmlWindow.setFramerateLimit(amount);
}

void Canvas::setPosition(Vector2D position)
{
    this->position = position;
    
    sfmlWindow.setPosition(sf::Vector2i(position.x, position.y));
}

void Canvas::setSize(Vector2D size)
{
    this->size = size;
    
    sfmlWindow.setSize(sf::Vector2u(size.x, size.y));
    sfmlWindow.setView(sf::View(sf::FloatRect(0.0f, 0.0f, size.x, size.y)));
}

void Canvas::setTitle(std::string title)
{
    this->title = title;
    
    sfmlWindow.setTitle(sf::String(title));
}

bool Canvas::tick()
{
    // Prevent ticking when canvas is inactive
    if(!active) return false;
    
    sf::Event event;
    while(sfmlWindow.pollEvent(event))
        switch(event.type)
        {
            /* When SFML window gets closed, call `stop` method for terminating the
             * canvas and its fields safely and then destruct the SFML window. */
            case sf::Event::Closed:
                stop();
                return false;
            
            /* The rest of events are passed to the input parser, which interprets
             * them in context of all added rectangles. */
            default:
                inputParser.parseSfmlEvent(event);
                break;
        }

    // Request cleaning of the window content by SFML before drawing it again
    sfmlWindow.clear();

    /* Draw all rectangles by exploiting their one-way magic of friendship.
     * Call update method for each rectangle, no matter the visibility status. */
    for(Rectangle* r : rectanglePtrs)
    {
        r->onTick(tickCount);
        
        if(!r->isVisible()) continue;
        
        sfmlWindow.draw(r->sfmlRect);
        
        if(r->isUsingText())
        {
            // Rectangle is using a text, process it
            int rid             = r->getId();
            TextProperties* rtp = r->getText();
            
            if(rectangleTexts.find(rid) == rectangleTexts.end())
            {
                /* SFML Text is not created for the rectangle yet, do it and
                 * set the refresh flag of its text properties to induce the update. */
                rectangleTexts[rid] = sf::Text("", sfmlFont);
                rtp->refreshFlag = true;
            }
            
            // If the rectangle set the refresh flag, update SFML text with properties data
            if(rtp->refreshFlag)
            {
                // Update SFML text with properties & rectangle's data
                sf::Text* sfmlTextPtr = &rectangleTexts[rid];
                sfmlTextPtr->setFillColor(sf::Color(rtp->color.r, rtp->color.g, rtp->color.b)); // color
                sfmlTextPtr->setString(rtp->content);                                           // content
                sfmlTextPtr->setCharacterSize(rtp->size);                                       // size
                sfmlTextPtr->setPosition(sf::Vector2f(r->getX(), r->getY()));
                
                // Update the properties data themselves
                rtp->refreshFlag    =   false;                                                  // refreshFlag
                rtp->width          =   sfmlTextPtr->findCharacterPos(rtp->content.size()).x -  // width
                                        sfmlTextPtr->findCharacterPos(0).x;
            }
            
            sfmlWindow.draw(rectangleTexts[rid]);
        }
        else if(rectangleTexts.find(r->getId()) != rectangleTexts.end())
        {
            /* Rectangle have associated SFML text defined, but it stopped declaring
             * its usage, therefore destroy the text. */
             rectangleTexts.erase(r->getId());
        }
    }
    
    /* Request display of the rectangles to SFML, which automatically handles previously
     * specified drawing rate. */
    sfmlWindow.display();
    tickCount++;
    return true;
}
