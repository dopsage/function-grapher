
#include "FunctionEntry.hpp"

using namespace sgf;

FunctionEntry:: FunctionEntry() :
                Rectangle::Rectangle(),
                button(),
                input()
{
    setButtonListener(nullptr);
    setButtonWidth(50.0f);
}

void FunctionEntry::copy(Rectangle* other)
{
    Rectangle::copy(other);
    
    /* Assuming copying target is a function entry (it must be).
     * The instance fields are copied lastly. */
    FunctionEntry* ofe = (FunctionEntry*)other;
    
    button  .copy(ofe->getButtonPtr());
    input   .copy(ofe->getTextInputPtr());
    
    setButtonListener   (ofe->getButtonPtr()->getListener());
    setButtonWidth      (ofe->getButtonPtr()->getWidth());
}

FunctionData FunctionEntry::getFunctionData() const
{
    return { "Lun", [](float x) { return x * x; } };
}

Button* FunctionEntry::getButtonPtr()
{
    return &button;
}

TextInput* FunctionEntry::getTextInputPtr()
{
    return &input;
}

void FunctionEntry::onAdd()
{
    getCanvasPtr()->add(&button);
    getCanvasPtr()->add(&input);
}

void FunctionEntry::onRemove()
{
    getCanvasPtr()->remove(&button);
    getCanvasPtr()->remove(&input);
}

void FunctionEntry::setButtonListener(sgf::ButtonListener listener)
{
    button.setListener(listener);
}

void FunctionEntry::setButtonWidth(float width)
{
    button.setSize({ width < 0.0f ? 0.0f : width, button.getHeight() });
}

void FunctionEntry::setPosition(Vector2D position)
{
    button.setPosition({
		button.getX() - this->getX() + position.x,
		button.getY() - this->getY() + position.y,
	});
    input.setPosition({
		input.getX() - this->getX() + position.x,
		input.getY() - this->getY() + position.y,
	});
    
	Rectangle::setPosition(position);
}

void FunctionEntry::setPriority(int priority)
{
    Rectangle::  setPriority(priority);
	button      .setPriority(priority + 1);
    input       .setPriority(priority + 1);
}

void FunctionEntry::setSize(Vector2D size)
{
    Rectangle::setSize(size);

    // Button is always on the right to the text input, they stick together
    button  .setPosition({
        this->getX() + this->getWidth() - button.getWidth(),
        this->getY()
    });
    button  .setSize({ button.getWidth(), this->getHeight() });
    input   .setSize({ this->getWidth() - button.getWidth(), this->getHeight() });
}

void FunctionEntry::setVisible(bool visible)
{
    Rectangle::  setVisible(visible);
    button      .setVisible(visible);
    input       .setVisible(visible);
}
