
#include "SGF/Slider.hpp"

void sgf::Slider::onHandleMouseEvent(sgf::MouseEvent event, sgf::Vector2D position, int id, sgf::Canvas* canvas)
{
	/* It is known, that the listening rectangle is actually the slider handle,
     * therefore pointer cast is a safe way of accessing the instance. */
	sgf::Rectangle* handle = (sgf::Rectangle*)canvas->getRectangle(id);
    
    /* After all, it is also guaranteed that metadata of the handle instance obtained 
     * above is the controlling slider instance, therefore can perform pointer cast. */
	sgf::Slider* slider = (sgf::Slider*)handle->getMeta();
	
	if(event == sgf::MouseEvent::DOWN)
	{
		slider->isHandleMouseDown = true;
		slider->handleDeltaY      = handle->getY() - position.y;
	}
	else if(slider->isHandleMouseDown && event == sgf::MouseEvent::MOVE)
	{
		// Clamp the slider Y position to the canvas visible area
		float handleLimitY = slider->getY() + slider->getHeight() - handle->getHeight();
		float nextHandleY  = position.y + slider->handleDeltaY;
		nextHandleY = nextHandleY < slider->getY() ? slider->getY() : (nextHandleY > handleLimitY ? handleLimitY : nextHandleY);
		
		// Use clamped position to update the slider handle
		handle->setPosition({ handle->getX(), nextHandleY });
		
		// Update slider value
		slider->value = handle->getY() / handleLimitY;
        
        /* Invoke the slider listener because the slider value has just changed.
         * It is possible to access private members since we are still in a member
         * (this static function) of a class to which these private fields belong. */
        slider->sliderListener(slider->value, slider->getID(), canvas);
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
					value(0.F)
{
	this->handle.setMouseListener(sgf::Slider::onHandleMouseEvent);
    
    /* Adjust the handle to defaults, and make the slider instance its metadata
     * for sake of handle callback set above. */
    this->setHandleHeight(50.F);
    this->handle.setMeta(this);
}

sgf::Rectangle& sgf::Slider::getHandle()
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

sgf::Rectangle& sgf::Slider::setVisible(bool visible)
{
    sgf::Rectangle::setVisible(visible);
    
    // Handle visibility is dependant on background's
    handle.setVisible(visible);
    
    return *this;
}

sgf::Slider& sgf::Slider::setSliderListener(sgf::SliderListener callback)
{
    this->sliderListener = callback;
    return *this;
}

// TODO: Consider if getHandle could be allowed to change instead of reduntant methods like this

sgf::Slider& sgf::Slider::setHandleHeight(float height)
{
    // I cannot really have an idea on why one would need a getter for handle height
	this->handle.setSize({ handle.getWidth(), height });
    return *this;
}
