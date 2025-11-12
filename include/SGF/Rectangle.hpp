
/********** SIMPLE GUI FRAMEWORK RECTANGLE MODULE **********/

#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include "SFML/Graphics.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

// This class needs to be refactored so it is readable for future me or other devs,
// Thank you Alj for believing in this challenge to make this class virtual, meaning
// compatible with derivation (Slider).
class Rectangle
{
friend class Canvas;  // allows it to draw this thing fast

private:
	mutable Color3D	   color;
    KeyboardListener   keyboardListener;
    void*			   keyboardPayload;
    MouseListener      mouseListener;
    void*			   mousePayload;
	Vector2D 		   position;
	int 			   priority;
	sf::RectangleShape sfmlRect;
	Vector2D 		   size;

public:
	Rectangle();
	virtual ~Rectangle() = default;
	virtual Color3D		getColor() const;
	virtual Vector2D 	getPosition() const;
	int 	 			getPriority() const;
	virtual Vector2D 	getSize() const;
    float               getHeight() const;
    float               getWidth() const;
    float               getX() const;
    float               getY() const;
    void                onKeyboardInput(Unicode data) const;
    void                onMouseInput(MouseEvent event, Vector2D position) const;
	virtual Rectangle&	setColor(Color3D color);
    Rectangle&          setKeyboardListener(KeyboardListener callback, void* payload);
    Rectangle&          setMouseListener(MouseListener callback, void* payload);
	virtual Rectangle& 	setPosition(Vector2D position);
	virtual Rectangle& 	setPriority(int priority);
	virtual Rectangle& 	setSize(Vector2D size);
};

}

#endif
