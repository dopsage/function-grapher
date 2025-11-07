
#include "SGF/Rectangle.hpp"

sgf::Rectangle::Rectangle()
{
	this->sfmlRect = sf::RectangleShape();
}

sgf::Rectangle::Rectangle(sgf::Vector2D position, sgf::Vector2D size, int priority) : Rectangle()
{
	this->setPosition(position);
	this->setPriority(priority);
	this->setSize(size);
}

sgf::Color3D sgf::Rectangle::getColor() const
{
	return this->color;
}

sgf::Vector2D sgf::Rectangle::getPosition() const
{
	return this->position;
}

int sgf::Rectangle::getPriority() const
{
	return this->priority;
}

const sf::RectangleShape& sgf::Rectangle::getSfmlRect() const
{
	return this->sfmlRect;
}

sgf::Vector2D sgf::Rectangle::getSize() const
{
	return this->size;
}

sgf::Rectangle& sgf::Rectangle::setColor(sgf::Color3D color)
{
	this->color = color;
	this->sfmlRect.setFillColor(sf::Color(color.r, color.g, color.b));
	return *this;
}

sgf::Rectangle& sgf::Rectangle::setPosition(sgf::Vector2D position)
{
	this->position = position;
	this->sfmlRect.setPosition(sf::Vector2f(position.x, position.y));
	return *this;
}

sgf::Rectangle& sgf::Rectangle::setPriority(int priority)
{
	this->priority = priority;
	return *this;
}

sgf::Rectangle& sgf::Rectangle::setSize(sgf::Vector2D size)
{
	this->size = size;
	this->sfmlRect.setSize(sf::Vector2f(size.x, size.y));
	return *this;
}
