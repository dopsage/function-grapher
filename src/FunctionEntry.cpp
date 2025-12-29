
#include "FunctionEntry.hpp"

void FunctionEntry::onButtonEvent(int id, sgf::Canvas* canvas)
{
    FunctionEntry* feEntry = (FunctionEntry*)canvas->getRectangle(id)->getMeta();
    
    if(feEntry->parentList != nullptr)
    {
        feEntry->parentList->remove((Rectangle*)feEntry);
    }
        
}

FunctionEntry::FunctionEntry() :
                      button(),
                       input(),
                  parentList(nullptr)
{
    button.setButtonListener(FunctionEntry::onButtonEvent);
    button.setMeta(this);
}

void FunctionEntry::copy(sgf::Rectangle* other)
{
    sgf::Rectangle::copy(other);
    
// Assuming that developers are well slept ...
    FunctionEntry* feOther = (FunctionEntry*)other;
    
    button  .copy(&feOther->getButton());
    button  .setMeta(this); // This is necessary!
    input   .copy(&feOther->getTextInput());
    
    setParentList(&feOther->getParentList());
}

FunctionData FunctionEntry::getData() const
{
    return { "Lun", [](float x) { return x * x; } };
}

sgf::VList& FunctionEntry::getParentList()
{
    return *parentList;
}

sgf::TextProperties* FunctionEntry::getText()
{
    return nullptr;
}

sgf::Button& FunctionEntry::getButton()
{
    return this->button;
}

sgf::TextInput& FunctionEntry::getTextInput()
{
    return this->input;
}

bool FunctionEntry::isValid() const
{
    return true;
}

void FunctionEntry::onAdd()
{
    canvas->add(button);
    canvas->add(input);
}

void FunctionEntry::onRemove()
{
    canvas->remove(button);
    canvas->remove(input);
}

void FunctionEntry::setColor(sgf::Color3D color)
{
    sgf::Rectangle::setColor(color);
}

// NOTICE: THIS IS ONLY FOR THIS CLASS, YOU STILL NEED TO ADD ENTRY TO VLIST MANUALLY
void FunctionEntry::setParentList(sgf::VList* list)
{
    this->parentList = list;
}

void FunctionEntry::setPosition(sgf::Vector2D position)
{
    button.setPosition({
		button.getX() - getX() + position.x,
		button.getY() - getY() + position.y,
	});
    input.setPosition({
		input.getX() - getX() + position.x,
		input.getY() - getY() + position.y,
	});
    
	sgf::Rectangle::setPosition(position);
}

void FunctionEntry::setPriority(int priority)
{
    sgf::Rectangle::setPriority(priority);
    
	button.setPriority(priority);
    input.setPriority(priority);
}

void FunctionEntry::setSize(sgf::Vector2D size)
{
    sgf::Rectangle::setSize(size);

// Proportions needs commonization!
    button.setPosition({ getX() + getWidth() * 0.8F, getY() });
    button.setSize({ getWidth() * 0.2F, getHeight() });
    input.setSize({ getWidth() * 0.8F, getHeight() });
}

void FunctionEntry::setText(sgf::TextProperties* properties)
{
    // Ignore
}

void FunctionEntry::setVisible(bool visible)
{
    sgf::Rectangle::setVisible(visible);
    
    button.setVisible(visible);
    input.setVisible(visible);
}
