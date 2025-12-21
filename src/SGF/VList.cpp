
#include "SGF/VList.hpp"

#include<iostream>
void sgf::VList::updateBounds()
{
    // List resizes its width to maximum one, and height to total one
    
    float maxWidth = 0.F;
    float totalHeight = 0.F;
    for(Rectangle* member : this->members)
    {
        if(member->getWidth() > maxWidth)
            maxWidth = member->getWidth();
        
        totalHeight += member->getHeight();
    }
    
    sgf::Rectangle::setSize({ maxWidth, totalHeight });
}

sgf::VList::VList() :
          members()
{
    
    /* Initialize the area rectangle, which is this instance.
     * Base method definitions are used because some of them are overriden to do
     * nothing in order to disallow external code from interferring. */
    sgf::Rectangle::setSize({ 0, 0 });
    sgf::Rectangle::setVisible(false);
}

int sgf::VList::getMemberCount() const
{
    return this->members.size();
}

sgf::Rectangle* sgf::VList::getMemberRectangle(int index)
{
    return (index < 0 || index >= getMemberCount()) ? nullptr : members.at(index);
}

void sgf::VList::insertMember(int index, Rectangle& newMember)
{
    // Sum heights until the insertion index to obtain the new member height offset
    float   offset  = 0.F;
    int     mi      = 0;  // Member index
    for(; mi < index; mi++)
        offset += getMemberRectangle(mi)->getHeight();
    
    // Add the new rectangle visually and logically
    newMember.setPosition({ getX(), getY() + offset });
    members.insert(members.begin() + mi, &newMember);
    mi++;
    
    // Move rectangles past the inserted one down by its height
    for(; mi < getMemberCount(); mi++)
    {
        Rectangle* currMember = getMemberRectangle(mi);
        currMember->setPosition({ getX(), currMember->getY() + newMember.getHeight() });
    }
    
    this->updateBounds();
}

void sgf::VList::removeMember(int index)
{
    Rectangle* targetMember = getMemberRectangle(index);
    float offset = targetMember->getHeight();
    
    for(int mi = index + 1; mi < getMemberCount(); mi++)
    {
        Rectangle* currMember = getMemberRectangle(mi);
        currMember->setPosition({ getX(), getY() - offset });
    }
    
    // Remove the target rectangle
    this->canvas->remove(*targetMember);
    
    this->updateBounds();
}

sgf::Rectangle& sgf::VList::setColor(sgf::Color3D color)
{
    // Ignore
    
    return *this;
}

sgf::Rectangle& sgf::VList::setPosition(sgf::Vector2D position)
{
    // Move all inserted rectangles together with the area
    // ...
    
	Rectangle::setPosition(position);
    
	return *this;
}

sgf::Rectangle& sgf::VList::setPriority(int priority)
{
    // All inserted rectangles receive the same priority as area
    // ...
    
    sgf::Rectangle::setPriority(priority);
    
	return *this;
}

sgf::Rectangle& sgf::VList::setSize(sgf::Vector2D size)
{
    // Ignore
    
    return *this;
}

sgf::Rectangle& sgf::VList::setText(sgf::TextProperties* properties)
{
    // Ignore
    
    return *this;
}

sgf::Rectangle& sgf::VList::setVisible(bool visible)
{
    // Area is always hidden, but for inserted rectangles it is not the case
    // ...
    
    return *this;
}
