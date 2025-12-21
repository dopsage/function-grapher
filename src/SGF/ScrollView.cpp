
#include "SGF/ScrollView.hpp"

#include<iostream>
void sgf::ScrollView::onSliderEvent(float value, int id, Canvas* canvas)
{
    sgf::Slider*        slider      = (sgf::Slider*)canvas->getRectangle(id);
    sgf::ScrollView*    scrollView  = (sgf::ScrollView*)slider->getMeta();
    
    /* Now manage the logical rectangle `list` to move and resize accordingly
     * Here it would only be moved but add some methods for adding other rectangles to the view
     * and there you would resize the list etc... logic! */
    scrollView->getList().setPosition({ value*100, value+100 });
    std::cout << "-> " << scrollView->getList().getX() << std::endl;
}

sgf::ScrollView::ScrollView() :
                       list(),
                     slider()
{
    this->slider.setSliderListener(sgf::ScrollView::onSliderEvent);
    
    /* Adjust list and slider to defaults, and make the scroll view instance its
     * metadata for sake of managing this instance "remotely" from callback. */
    this->list.setVisible(false);
    this->setSliderWidth(25.F);
    this->slider.setMeta(this);
}

sgf::Rectangle& sgf::ScrollView::getList()
{
    return this->list;
}

sgf::Slider& sgf::ScrollView::getSlider()
{
    return this->slider;
}

sgf::Rectangle& sgf::ScrollView::setColor(sgf::Color3D color)
{
    sgf::Rectangle::setColor(color);
    
    // Slider color is some derivative of the area's
	this->slider.setColor({ (sgf::Byte)(255 - color.r), color.g, (sgf::Byte)(255 - color.b) });
    
    return *this;
}

sgf::Rectangle& sgf::ScrollView::setPosition(sgf::Vector2D position)
{
    // First move the list and the slider according to the new area's position
    this->list.setPosition({
		list.getX() - getX() + position.x,
		list.getY() - getY() + position.y,
	});
    this->slider.setPosition({
		slider.getX() - getX() + position.x,
		slider.getY() - getY() + position.y,
	});
    
    
	Rectangle::setPosition(position);
    
	return *this;
}

sgf::Rectangle& sgf::ScrollView::setPriority(int priority)
{
    sgf::Rectangle::setPriority(priority);
    
    // List and slider priority is the same as the area's
    this->list.setPriority(priority);
	this->slider.setPriority(priority);
    
	return *this;
}

sgf::Rectangle& sgf::ScrollView::setSize(sgf::Vector2D size)
{
    sgf::Rectangle::setSize(size);
    
    this->list.setSize({ getWidth() - slider.getWidth(), getHeight() });
    this->slider.setSize({ slider.getWidth(), getHeight() });
    
    return *this;
}

sgf::ScrollView& sgf::ScrollView::setSliderWidth(float width)
{
    // List needs to be offset by slider width along X axis
    this->list.setPosition({ getX() + width, getY() });
    
    this->slider.setSize({ width, getHeight() });
    
    return *this;
}

sgf::Rectangle& sgf::ScrollView::setText(sgf::TextProperties* properties)
{
    // Ignore
    return *this;
}

sgf::Rectangle& sgf::ScrollView::setVisible(bool visible)
{
    sgf::Rectangle::setVisible(visible);
    
    // Slider visibility is dependant on area's
    this->slider.setVisible(visible);
    
    return *this;
}
