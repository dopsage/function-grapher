
/********** SIMPLE GUI FRAMEWORK VERTICAL LIST MODULE **********/

#ifndef _VLIST_HPP
#define _VLIST_HPP

#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"

namespace sgf
{

/* DESC */
class VList : public Rectangle
{
private:
    void            updateBounds();
    RectangleVector members;

public:
    VList();
    int         getMemberCount() const;
    Rectangle*  getMemberRectangle(int index);
    void        insertMember(int index, Rectangle& rect);
    void        removeMember(int index);
    Rectangle&  setColor(Color3D color) override;
    Rectangle&  setPosition(Vector2D position) override;
    Rectangle&  setPriority(int priority) override;
    Rectangle&  setSize(Vector2D size) override;
    Rectangle&  setText(TextProperties* properties) override;
    Rectangle&  setVisible(bool visible) override;
};

}

#endif
