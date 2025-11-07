
/********** SIMPLE GUI FRAMEWORK RECTANGLE MODULE **********/

#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include "SFML/Graphics.hpp"

namespace sgf
{

typedef unsigned char byte;

// Simple 2-dimensional vector data structure
struct Vector2D
{
	float x;
	float y;
};

// Simple 3-dimensional (RGB) color data structure
struct Color3D
{
	byte r;
	byte g;
	byte b;
};

/*  */
class Rectangle
{
private:
	Color3D			   color;
	Vector2D 		   position;
	int 			   priority;
	sf::RectangleShape sfmlRect;
	Vector2D 		   size;

public:
	Rectangle();
	Rectangle(Vector2D position, Vector2D size, int priority = 0);
	Color3D					  getColor()    const;
	Vector2D 				  getPosition() const;
	int 	 				  getPriority() const;
	const sf::RectangleShape& getSfmlRect() const;
	Vector2D 				  getSize() 	const;
	Rectangle&				  setColor(Color3D color);
	Rectangle& 	 			  setPosition(Vector2D position);
	Rectangle& 	 			  setPriority(int priority);
	Rectangle& 	 			  setSize(Vector2D size);
};

}

#endif
