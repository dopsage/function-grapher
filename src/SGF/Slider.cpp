
#include "SGF/Slider.hpp"

const float sgf::Slider::HANDLE_HEIGHT = 50.F;

// SLIDER BEHAVIOUR
void sgf::Slider::onHandleMouseEvent(sgf::MouseEvent event, sgf::Vector2D position, void* payload)
{
	// Decode known payload!
	Slider* slider = (Slider*)payload;
	Rectangle* handle = (Rectangle*)&slider->getHandle();
	
	if(event == sgf::MouseEvent::DOWN)
	{
		slider->isHandleMouseDown = true;
		slider->handleDeltaY = handle->getY() - position.y;
	}
	else if(slider->isHandleMouseDown && event == sgf::MouseEvent::MOVE)
	{
		// Clamp the slider Y position to the canvas visible area.
		float handleLimitY = slider->getY() + slider->getHeight() - handle->getHeight();
		float nextHandleY  = position.y + slider->handleDeltaY;
		nextHandleY = nextHandleY < slider->getY() ? slider->getY() : (nextHandleY >= handleLimitY ? handleLimitY : nextHandleY);
		
		// Use clamped position to update the slider handle.
		handle->setPosition({ handle->getX(), nextHandleY });
		
		// Update slider value.
		slider->value = handle->getY() / handleLimitY;
	}
	else if(event == sgf::MouseEvent::UP)
	{
		slider->isHandleMouseDown = false;
	}
}

sgf::Slider::Slider() :
sgf::Rectangle::Rectangle(),
				   handle(),
		     handleDeltaY(0.F),
	    isHandleMouseDown(false),
					value(0.F)
{
	this->handle.setMouseListener(sgf::Slider::onHandleMouseEvent, this);
}

const sgf::Rectangle& sgf::Slider::getHandle() const
{
	return this->handle;
}

float sgf::Slider::getValue() const
{
	return this->value;
}

sgf::Rectangle& sgf::Slider::setColor(Color3D color)
{
	sgf::Rectangle::setColor(color);
	
	// Define default handle color ...
	this->handle.setColor({ 255 - color.r, 255 - color.g, 255 - color.b });
	return *this;
}

sgf::Rectangle& sgf::Slider::setPosition(sgf::Vector2D position)
{
	handle.setPosition({
		handle.getX() - getX() + position.x,
		handle.getY() - getY() + position.y,
	});
	Rectangle::setPosition(position);
	return *this;
}

sgf::Rectangle& sgf::Slider::setPriority(int priority)
{
	sgf::Rectangle::setPriority(priority);
	this->handle.setPriority(priority);
	return *this;
}

sgf::Rectangle& sgf::Slider::setSize(sgf::Vector2D size)
{
	sgf::Rectangle::setSize(size);
	handle.setSize({ getWidth(), sgf::Slider::HANDLE_HEIGHT });
	return *this;
}

void sgf::Slider::setHandleHeight(float height)
{
	this->handle.setSize({ handle.getWidth(), height });
}
