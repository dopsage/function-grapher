
/********** SIMPLE GUI FRAMEWORK SCROLL VIEW MODULE **********/

#ifndef _SCROLLVIEW_HPP
#define _SCROLLVIEW_HPP

#include "SGF/Rectangle.hpp"
#include "SGF/Slider.hpp"
#include "SGF/VList.hpp"

namespace sgf
{

/* DESC */
class ScrollView : public Rectangle
{
private:
    VList       list;
    static void onSliderEvent(float value, int id, Canvas* canvas);
    Slider      slider;

public:
    ScrollView();
    VList&  getList();
    void    onAdd() override;
    void    setColor(Color3D color) override;
    void    setPosition(Vector2D position) override;
    void    setPriority(int priority) override;
    void    setSize(Vector2D size) override;
    void    setSliderWidth(float width);
    void    setText(TextProperties* properties) override;
    void    setVisible(bool visible) override;
};

}

#endif
