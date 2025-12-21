
/********** SIMPLE GUI FRAMEWORK SCROLL VIEW MODULE **********/

#ifndef _SCROLLVIEW_HPP
#define _SCROLLVIEW_HPP

#include "SGF/Rectangle.hpp"
#include "SGF/Slider.hpp"

namespace sgf
{

/* DESC */
class ScrollView : public Rectangle
{
private:
    Rectangle   list;
    static void onSliderEvent(float value, int id, Canvas* canvas);
    Slider      slider;

public:
    ScrollView();
    Rectangle&  getList();
    Slider&     getSlider();
    Rectangle&  setColor(Color3D color) override;
    Rectangle&  setPosition(Vector2D position) override;
    Rectangle&  setPriority(int priority) override;
    Rectangle&  setSize(Vector2D size) override;
    ScrollView& setSliderWidth(float width);
    Rectangle&  setText(TextProperties* properties) override;
    Rectangle&  setVisible(bool visible) override;
};

}

#endif
