
#include "SGF/TextInput.hpp"

const int sgf::TextInput::uniBackspace = 8;

const int sgf::TextInput::uniReturn = 13;

#include <iostream>
void sgf::TextInput::onFieldKeyboardEvent(sgf::Unicode data, int id, sgf::Canvas* canvas)
{
    if(data == sgf::TextInput::uniReturn)
    {
        // Field received carriage return, finish its listening of keyboard (deselect)
        std::cout << "<Return>" << std::endl;
        canvas->getInputParser().setKeyboardReceiver(nullptr);
    }
    else if(data == sgf::TextInput::uniBackspace)
    {
        // Field received backspace, remove last character from the current input text
        std::cout << "<Backspace>" << std::endl;
    }
    else
    {
        // Field received some ordinary textual character, update the input text
        std::cout << data << std::endl;
    }
}

void sgf::TextInput::onFieldMouseEvent(sgf::MouseEvent event, sgf::Vector2D position, int id, sgf::Canvas* canvas)
{
    // Clicking mechanic works is really similar to the one defined for Slider
    
    sgf::Rectangle* field = canvas->getRectangle(id);
    sgf::TextInput* input = (sgf::TextInput*)field->getMeta();
    
    if(event == sgf::MouseEvent::DOWN)
    {
        input->isFieldMouseDown = true;
    }
    else if(input->isFieldMouseDown && event == sgf::MouseEvent::UP && field->contains(position))
    {
        // Field got clicked on, set it as keyboard listener (select)
        canvas->getInputParser().setKeyboardReceiver(field);
        
        input->isFieldMouseDown = false;
    }
}

sgf::TextInput::TextInput() :
                      field(),
           isFieldMouseDown(false),
                    leftPad(0.F),
                    vertPad(0.F)
{
    this->field.setKeyboardListener(sgf::TextInput::onFieldKeyboardEvent);
    this->field.setMouseListener(sgf::TextInput::onFieldMouseEvent);
    
    this->field.setMeta(this);
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
