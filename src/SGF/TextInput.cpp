
#include "SGF/TextInput.hpp"

const int sgf::TextInput::keyBackspace = -59;
const int sgf::TextInput::keyLeftArrow = -71;
const int sgf::TextInput::keyReturn = -58;
const int sgf::TextInput::keyRightArrow = -72;

void sgf::TextInput::onFieldKeyboardEvent(int data, int id, sgf::Canvas* canvas)
{
	// Assume metadata of the field instance is set to the parenting text input instance
	sgf::Rectangle* field = canvas->getRectangle(id);
	sgf::TextInput* input = (sgf::TextInput*)field->getMeta();
    
	switch(data)
	{
		case sgf::TextInput::keyBackspace:
		{
			// Field received backspace, remove last character from the current input text
			if(input->cursorPosition > -1)
			{
				std::string updated = std::string(*input->getContent());
				updated.erase(input->cursorPosition, 1);
				input->setContent(updated);
                input->cursorPosition--;
			}
			break;
		}
		case sgf::TextInput::keyLeftArrow:
		{
			// Field received left arrow, move cursor by one to left (limit to -1)		
			input->cursorPosition = (input->cursorPosition > -1) ? (input->cursorPosition - 1) : (-1);
			break;
		}
		case sgf::TextInput::keyReturn:
		{
			// Field received carriage return, finish its listening of keyboard (deselect)
			canvas->getInputParser().setKeyboardReceiver(nullptr);
			break;
		}
		case sgf::TextInput::keyRightArrow:
		{
			// Field received right arrow, move cursor by one to right (limit to length-1)
			input->cursorPosition = (input->cursorPosition < input->getContent()->length() - 1) ? 
									(input->cursorPosition + 1) :
									(input->getContent()->length() - 1);
			break;
		}
		default:
		{
			if(
// TODO: Implement some serious filter
				(data >= 65 && data <= 90) ||	// Big letters
				(data >= 97 && data <= 122) ||	// Small letters
				data == 32 ||					// Space ` `
				data == 46 ||					// Period `.`
				data == 44						// Comma `,`
			)
			{
				// Field received some other unicode, insert it into content string	
				std::string updated = std::string(*input->getContent());
				updated.insert(input->cursorPosition + 1, 1, (char)data);
				input->setContent(updated);
				input->cursorPosition++;
			}
			break;
		}
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
        /* Field got clicked on, set it as keyboard listener (select).
         * Do not forget about resetting cursor position to the end of the input. */
        input->cursorPosition = input->getContent()->length() - 1; 
        canvas->getInputParser().setKeyboardReceiver(field);
        
        input->isFieldMouseDown = false;
    }
}

sgf::TextInput::TextInput() :
			 cursorPosition(0),
                      field(),
           isFieldMouseDown(false),
                    leftPad(0.F),
                    vertPad(0.F)
{
    this->field.setKeyboardListener(sgf::TextInput::onFieldKeyboardEvent);
    this->field.setMouseListener(sgf::TextInput::onFieldMouseEvent);
    
    this->field.setMeta(this);
}

const std::string* sgf::TextInput::getContent()
{
	return &field.getText()->content;
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

sgf::TextInput& sgf::TextInput::setContent(const std::string& content)
{
	// Set just the content field of the set text properties
	field.getText()->content = content;
	field.updateText();
	
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
