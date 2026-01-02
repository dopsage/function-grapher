
#include "SGF/VList.hpp"

void sgf::VList::updateBounds()
{
    float maxWidth      = 0.F;
    float totalHeight   = 0.F;
    for(Rectangle* member : members)
    {
        // List width is the same as the widest member's
        maxWidth     = (member->getWidth() > maxWidth) ? member->getWidth() : maxWidth;
        // List height is the sum of all members' heights
        totalHeight += member->getHeight();
    }
    
    sgf::Rectangle::setSize({ maxWidth, totalHeight });
}

sgf::VList::VList() :
          members(),
            toAdd()
{    
    // This instance acts as a rather logic rectangular container
    sgf::Rectangle::setSize({ 0, 0 });
}

int sgf::VList::getCount() const
{
    return this->members.size();
}

sgf::Rectangle* sgf::VList::getMember(int index)
{
    return (index < 0 || index >= getCount()) ? nullptr : members.at(index);
}

void sgf::VList::insert(int index, sgf::Rectangle* newMember)
{
    // Sum of heights of members with indices below `index` is the `newMember` offset
    float   offset  = 0.F;
    int     mi      = 0;
    for(; mi < index; mi++)
    {
        offset += getMember(mi)->getHeight();
    }
    
    // New rectangle `newMember` is added to the list both visually and logically
    newMember->setPosition({ getX(), getY() + offset });
    newMember->setPriority(getPriority());
    newMember->setVisible(isVisible());
    members.insert(members.begin() + mi, newMember);
    mi++;
    
    // Manage registering the new member in canvas
    if(getCanvasPtr() == nullptr)   toAdd.push_back(newMember);
    else                    getCanvasPtr()->add(*newMember);
    
    // Members with indices above `index` need to be moved by `newMember` height down
    for(; mi < getCount(); mi++)
    {
        Rectangle* currMember = getMember(mi);
        currMember->setPosition({ getX(), currMember->getY() + newMember->getHeight() });
    }
    
    // Reach of the list is finally updated to fit new contents
    this->updateBounds();
}

void sgf::VList::onAdd()
{
    /* Now the list contains reference to canvas, add all members which were already
     * processed but not yet registered on canvas before this moment. */
    while(!toAdd.empty())
    {
        getCanvasPtr()->add(**toAdd.begin());
        toAdd.erase(toAdd.begin());
    }
}

void sgf::VList::onRemove()
{
// Not checked
    for(int mi = 0; mi < getCount(); mi++)
        getCanvasPtr()->remove(*getMember(mi));
    
    members.clear();
}

void sgf::VList::remove(int index)
{
    // Members with indices above `index` need to be moved by target member height up
    Rectangle*  targetMember = getMember(index);
    float       targetHeight = targetMember->getHeight();
    for(int mi = index + 1; mi < getCount(); mi++)
    {
        Rectangle* currMember = getMember(mi);
        currMember->setPosition({ getX(), currMember->getY() - targetHeight });
    }
    
    // Target rectangle is removed from the list
    this->members.erase(members.begin() + index);
    
    // Manage unregistering the new member in canvas
    if(getCanvasPtr() == nullptr)
    {
        auto it = std::find(toAdd.begin(), toAdd.end(), targetMember);
        if(it != toAdd.end()) toAdd.erase(it);
    }
    else getCanvasPtr()->remove(*targetMember);
    
    // List size needs an update
    this->updateBounds();
}

void sgf::VList::remove(sgf::Rectangle* target)
{
    for(int mi = 0; mi < getCount(); mi++)
        if(getMember(mi) == target)
            remove(mi);
}

void sgf::VList::setColor(sgf::Color3D color)
{
    // Ignore
}

void sgf::VList::setPosition(sgf::Vector2D position)
{
    // Move all inserted rectangles together with the area
    for(int mi = 0; mi < getCount(); mi++)
    {
        Rectangle* member = getMember(mi);
        member->setPosition({ position.x, member->getY() - getY() + position.y });
    }
    
	Rectangle::setPosition(position);
}

void sgf::VList::setPriority(int priority)
{
    sgf::Rectangle::setPriority(priority);
    
    // All inserted rectangles receive the same priority as area
    for(int mi = 0; mi < getCount(); mi++)
        getMember(mi)->setPriority(priority);
}

void sgf::VList::setSize(sgf::Vector2D size)
{
    // Ignore
}

void sgf::VList::setText(sgf::TextProperties* properties)
{
    // Ignore
}

void sgf::VList::setVisible(bool visible)
{
    sgf::Rectangle::setVisible(visible);
    
    // Area is always hidden, but for members it is not the case
    for(int mi = 0; mi < getCount(); mi++)
        getMember(mi)->setVisible(visible);
}
