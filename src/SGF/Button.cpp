
#include "SGF/Button.hpp"

void sgf::Button::onMouseEvent(sgf::MouseEvent event, sgf::Vector2D position, int id, sgf::Canvas* canvas)
{
	/* It is known, that the listening rectangle is actually a button, therefore
     * pointer cast is a safe way of accessing the instance. */
	sgf::Button* button = (sgf::Button*)canvas->getRectangle(id);
	
    /* Button feeds the listener only when both down and up mouse events occurred
     * in its rectangular bounds. */
	if(event == sgf::MouseEvent::DOWN)
	{
		button->isMouseDown = true;
	}
	else if(event == sgf::MouseEvent::UP && button->isMouseDown)
	{
		button->isMouseDown = false;
        if(button->contains(position))
            button->buttonListener(id, canvas);
	}
}

sgf::Button::Button() :
sgf::Rectangle::Rectangle(),
	          isMouseDown(false),
           buttonListener(nullptr)
{
	this->setMouseListener(sgf::Button::onMouseEvent);
}

sgf::Button& sgf::Button::setButtonListener(sgf::ButtonListener callback)
{
    this->buttonListener = callback;
    return *this;
}
