
/********** SIMPLE GUI FRAMEWORK RECTANGLE MODULE **********/

#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include "SFML/Graphics.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Literal SFML drawable rectangle wrapper, that introduces features of a primitive
 * interactive rectangular area. */
class Rectangle
{
    // Allow canvas to access `sfmlRect` in drawing purposes, we trust it on this
    friend class Canvas;

private:
    Canvas*            canvas;
	Color3D	           color;
    bool               containsText;
    int                id;
    KeyboardListener   keyboardListener;
    MouseListener      mouseListener;
    void*              meta;
    Vector2D 		   position;
	int 			   priority;
	sf::RectangleShape sfmlRect;
    sf::Text*          sfmlTextPtr;
	Vector2D 		   size;
    std::string        text;
    bool               visible;

public:
	Rectangle();
	virtual ~Rectangle() = default;
    bool             contains(Vector2D position) const;
	virtual Color3D	 getColor() const;
    bool             getContainsText() const;
    float            getHeight() const;
    int              getID() const;
    void*            getMeta();
	virtual Vector2D getPosition() const;
	int 	 		 getPriority() const;
	virtual Vector2D getSize() const;
    virtual const std::string& getText() const;
    float            getWidth() const;
    virtual bool     getVisible() const;
    float            getX() const;
    float            getY() const;
    
    // These two methods invoke keyboard and mouse listeners with given parameters 
    void               onKeyboardInput(Unicode data);
    void               onMouseInput(MouseEvent event, Vector2D position);
	
    virtual Rectangle& setColor(Color3D color);
    
    // Rectangle can store only one callback method per device.
    Rectangle&         setKeyboardListener(KeyboardListener callback);
    Rectangle&         setMouseListener(MouseListener callback);
    
    Rectangle&         setMeta(void* meta);
    virtual Rectangle& setPosition(Vector2D position);
	virtual Rectangle& setPriority(int priority);
	virtual Rectangle& setSize(Vector2D size);
    virtual Rectangle& setText(const std::string& text);
    virtual Rectangle& setVisible(bool visible);
};

}

#endif
