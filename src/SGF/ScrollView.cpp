
#include "SGF/ScrollView.hpp"

void sgf::ScrollView::onSliderEvent(float value, int id, Canvas* canvas)
{
    sgf::Slider*        slider      = (sgf::Slider*)canvas->getRectangle(id);
    sgf::ScrollView*    scrollView  = (sgf::ScrollView*)slider->getMetaPtr();

// TODO: Make handle resizement automatic according to list height?
    float offset = scrollView->getHeight() - scrollView->list.getHeight();
    scrollView->list.setPosition({ 
        scrollView->list.getX(),
        scrollView->getY() + value * std::min(0.F, offset)
    });
}

sgf::ScrollView::ScrollView() :
                       list(),
                     slider()
{
    this->slider.setSliderListener(sgf::ScrollView::onSliderEvent);
    
    /* Adjust slider to defaults, and make the scroll view instance its metadata
     * for sake of managing this instance's fields "remotely" from callback. */
    this->setSliderWidth(25.F);
    this->slider.setMetaPtr(this);
}

sgf::VList& sgf::ScrollView::getList()
{
    return this->list;
}

void sgf::ScrollView::onAdd()
{
    // Add other rectangle instances on canvas setting
    this->getCanvasPtr()->add(list);
    this->getCanvasPtr()->add(slider);
}

void sgf::ScrollView::setColor(sgf::Color3D color)
{
    sgf::Rectangle::setColor(color);
    
    // Slider color is some derivative of the area's
	this->slider.setColor({ (sgf::Byte)(255 - color.r), color.g, (sgf::Byte)(255 - color.b) });
}

void sgf::ScrollView::setPosition(sgf::Vector2D position)
{
    // First move the list and the slider according to the new area's position
    this->list.setPosition({ position.x + slider.getWidth(), list.getY() - getY() + position.y });
    this->slider.setPosition(position);
    
	Rectangle::setPosition(position);
}

void sgf::ScrollView::setPriority(int priority)
{
    sgf::Rectangle::setPriority(priority);
    
    // List and slider priority is just above the area's
    this->list.setPriority(priority);
	this->slider.setPriority(priority);
}

void sgf::ScrollView::setSize(sgf::Vector2D size)
{
    sgf::Rectangle::setSize(size);
    
    this->list.setSize({ getWidth() - slider.getWidth(), getHeight() });
    this->slider.setSize({ slider.getWidth(), getHeight() });
}

void sgf::ScrollView::setSliderWidth(float width)
{
    // List needs to be offset by slider width along X axis
    this->list.setPosition({ getX() + width, getY() });
    
    this->slider.setSize({ width, getHeight() });
}

void sgf::ScrollView::setText(sgf::TextProperties* properties)
{
    // Ignore
}

void sgf::ScrollView::setVisible(bool visible)
{
    sgf::Rectangle::setVisible(visible);
    
    // List and slider visibility is dependant on area's
    this->list.setVisible(visible);
    this->slider.setVisible(visible);
}
