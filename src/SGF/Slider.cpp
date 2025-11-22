
#include "SGF/Slider.hpp"

// SLIDER BEHAVIOUR
void sgf::Slider::onHandleMouseEvent(sgf::MouseEvent event, sgf::Vector2D position, void* payload)
{
	/* Decode payload, which is always the slider instance for which this handle
     * mouse event callback is serving dragging feature. */
	Slider*    slider = (Slider*)payload;
	Rectangle* handle = (Rectangle*)&slider->getHandle();
	
	if(event == sgf::MouseEvent::DOWN)
	{
		slider->isHandleMouseDown = true;
		slider->handleDeltaY = handle->getY() - position.y;
	}
	else if(slider->isHandleMouseDown && event == sgf::MouseEvent::MOVE)
	{
		// Clamp the slider Y position to the canvas visible area
		float handleLimitY = slider->getY() + slider->getHeight() - handle->getHeight();
		float nextHandleY  = position.y + slider->handleDeltaY;
		nextHandleY = nextHandleY < slider->getY() ? slider->getY() : (nextHandleY >= handleLimitY ? handleLimitY : nextHandleY);
		
		// Use clamped position to update the slider handle
		handle->setPosition({ handle->getX(), nextHandleY });
		
		// Update slider value
		slider->value = handle->getY() / handleLimitY;
        
        /* Invoke the slider listener because the slider value has changed.
         * It is possible to access private members since we are still in a member
         * (this static function) of a class to which these private fields belong. */
        slider->sliderListener(slider->value, slider->sliderPayload);
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
           sliderListener(nullptr),
            sliderPayload(nullptr),
					value(0.F)
{
	this->handle.setMouseListener(sgf::Slider::onHandleMouseEvent, this);
    // Adjust the handle to defaults
    this->handle.setSize({ handle.getWidth(), 50.F });
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
    // Handle color is an inverse of the background's
	this->handle.setColor({ (sgf::Byte)(255 - color.r), (sgf::Byte)(255 - color.g), (sgf::Byte)(255 - color.b) });
	return *this;
}

sgf::Rectangle& sgf::Slider::setPosition(sgf::Vector2D position)
{
    // First move the handle according to the new background's position
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
    // Handle priority is the same as the background's
	this->handle.setPriority(priority);
	return *this;
}

sgf::Rectangle& sgf::Slider::setSize(sgf::Vector2D size)
{
	sgf::Rectangle::setSize(size);
    // Handle width is dependant on the background's, but its height is variable
	handle.setSize({ getWidth(), handle.getHeight() });
	return *this;
}

sgf::Slider& sgf::Slider::setSliderListener(SliderListener callback, void* payload)
{
    this->sliderListener = callback;
    this->sliderPayload  = payload;
    return *this;
}

sgf::Slider& sgf::Slider::setHandleHeight(float height)
{
    // I cannot really have an idea on why one would need a getter for handle height
	this->handle.setSize({ handle.getWidth(), height });
    return *this;
}
