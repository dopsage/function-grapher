
/********** SIMPLE GUI FRAMEWORK RECTANGLE MODULE **********/

#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include "SFML/Graphics.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Literal SFML drawable rectangle wrapper, that introduces features of a primitive interactive
 * rectangular area. */
class Rectangle
{
    // Allow canvas to access `sfmlRect` in drawing purposes, we trust it on this
    friend class Canvas;

private:
	Color3D	           color;
    
    /* Marked as mutable because onKeyboardInput/onMouseInput use and do not change them, but
     * it is not guaranteed that the set listener callback methods adhere to this rule too, they
     * may actually write pointed payload. */
    mutable KeyboardListener keyboardListener;
    mutable void*			 keyboardPayload;
    mutable MouseListener    mouseListener;
    mutable void*			 mousePayload;
	
    Vector2D 		   position;
	int 			   priority;
	sf::RectangleShape sfmlRect;
	Vector2D 		   size;

public:
	Rectangle();
	virtual ~Rectangle() = default;
	virtual Color3D	 getColor() const;
	virtual Vector2D getPosition() const;
	int 	 		 getPriority() const;
	virtual Vector2D getSize() const;
    float            getHeight() const;
    float            getWidth() const;
    float            getX() const;
    float            getY() const;
    
    /* These two methods invoke keyboard and mouse listeners together with their respective payloads
     * in form of unspecified pointers (void*) set earlier.  */ 
    void                onKeyboardInput(Unicode data) const;
    void                onMouseInput(MouseEvent event, Vector2D position) const;
	
    virtual Rectangle&	setColor(Color3D color);
    
    /* Rectangle can store only one callback method per device. Additionally there is a possibility
     * of passing some payload, which set callbacks will receive as the last parameter.
     * You can use payload to let callback functions access some external data, but YOU MUST BE SURE
     * about what the payload really is, because you will need to cast it to appropriate pointer. */
    Rectangle&          setKeyboardListener(KeyboardListener callback, void* payload);
    Rectangle&          setMouseListener(MouseListener callback, void* payload);
    
    virtual Rectangle& 	setPosition(Vector2D position);
	virtual Rectangle& 	setPriority(int priority);
	virtual Rectangle& 	setSize(Vector2D size);
};

}

#endif
