
/********** SIMPLE GUI FRAMEWORK RECTANGLE MODULE **********/

#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include "SFML/Graphics.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

class Rectangle final
{
friend class Canvas;  // allows it to draw this thing fast

private:
	Color3D			   color;
    KeyboardListener   keyboardListener;
    MouseListener      mouseListener;
	Vector2D 		   position;
	int 			   priority;
	sf::RectangleShape sfmlRect;
	Vector2D 		   size;

public:
	Rectangle();
	Color3D				getColor() const;
	Vector2D 			getPosition() const;
	int 	 			getPriority() const;
	Vector2D 			getSize() const;
    float               getHeight() const;
    float               getWidth() const;
    float               getX() const;
    float               getY() const;
    void                onKeyboardInput(Unicode data) const;
    void                onMouseInput(MouseEvent event, Vector2D position) const;
	Rectangle&			setColor(Color3D color);
    Rectangle&          setKeyboardListener(KeyboardListener callback);
    Rectangle&          setMouseListener(MouseListener callback);
	Rectangle& 	 		setPosition(Vector2D position);
	Rectangle& 	 		setPriority(int priority);
	Rectangle& 	 		setSize(Vector2D size);
};

}

#endif
