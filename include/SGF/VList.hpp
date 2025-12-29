
/********** SIMPLE GUI FRAMEWORK VERTICAL LIST MODULE **********/

#ifndef _VLIST_HPP
#define _VLIST_HPP

#include <vector>
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"

namespace sgf
{

/* DESC */
class VList : public Rectangle
{
private:
    void            updateBounds();
    RectangleDeque  members;
    RectangleDeque  toAdd;

public:
    VList();
    int         getCount() const;
    Rectangle*  getMember(int index);
    void        insert(int index, Rectangle* rect);
    void        onAdd() override;
    void        onRemove() override;
    void        remove(int index);
    void        remove(Rectangle* target);
    void        setColor(Color3D color) override;
    void        setPosition(Vector2D position) override;
    void        setPriority(int priority) override;
    void        setSize(Vector2D size) override;
    void        setText(TextProperties* properties) override;
    void        setVisible(bool visible) override;
};

}

#endif
