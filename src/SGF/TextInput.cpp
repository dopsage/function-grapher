
#include "SGF/TextInput.hpp"

sgf::TextInput::TextInput() :
                      field(),
                    leftPad(0.F),
                    vertPad(0.F)
{
    
}

sgf::Rectangle& sgf::TextInput::getField()
{
    return this->field;
}

int sgf::TextInput::getLeftPadding() const
{
    return this->leftPad;
}

sgf::TextProperties* sgf::TextInput::getText()
{
    return nullptr;
}

int sgf::TextInput::getVerticalPadding() const
{
    return this->vertPad;
}

sgf::Rectangle& sgf::TextInput::setColor(sgf::Color3D color)
{
    sgf::Rectangle::setColor(color);
    
    // Field color is an inverse of the background's
	this->field.setColor({ (sgf::Byte)(255 - color.r), (sgf::Byte)(255 - color.g), (sgf::Byte)(255 - color.b) });
    
	return *this;
}

sgf::TextInput& sgf::TextInput::setLeftPadding(int padding)
{
    this->leftPad = padding;
    
    // Refresh position & size
    this->setPosition(this->getPosition());
    this->setSize(this->getSize()); 
    
    return *this;
}

sgf::Rectangle& sgf::TextInput::setPosition(sgf::Vector2D position)
{
    sgf::Rectangle::setPosition(position);
    
    this->field.setPosition({ getX() + this->leftPad, getY() + this->vertPad });
    
    return *this;
}

sgf::Rectangle& sgf::TextInput::setPriority(int priority)
{
    sgf::Rectangle::setPriority(priority);
    
    this->field.setPriority(priority);
    
    return *this;
}

sgf::Rectangle& sgf::TextInput::setSize(sgf::Vector2D size)
{
    sgf::Rectangle::setSize(size);
    
    this->field.setSize({ getWidth() - this->leftPad, getHeight() - 2 * this->vertPad });
    
    // Update size of the field text, if it is existent
    if(this->field.getContainsText())
    {
        field.getText()->size = field.getHeight();
        field.updateText();
    }
    return *this;
}

sgf::Rectangle& sgf::TextInput::setText(sgf::TextProperties* properties)
{
    return *this;
}

sgf::TextInput& sgf::TextInput::setVerticalPadding(int padding)
{
    this->vertPad = padding;
    
    // Refresh position & size
    this->setPosition(this->getPosition());
    this->setSize(this->getSize()); 
    
    return *this;
}

sgf::Rectangle& sgf::TextInput::setVisible(bool visible)
{
    sgf::Rectangle::setVisible(visible);
    
    this->field.setVisible(visible);
    
    return *this;
}
