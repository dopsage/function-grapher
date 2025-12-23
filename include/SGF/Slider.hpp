
/********** SIMPLE GUI FRAMEWORK SLIDER MODULE **********/

#ifndef _SLIDER_HPP
#define _SLIDER_HPP

#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Provides a vertical slider functionality by means of two rectangles. The class
 * derives from `Rectangle` to act as the slider background, it also stores a rectangle
 * instance that acts as the slider handle. */
class Slider final : public Rectangle
{
private:
	Rectangle   handle;
	float 		handleDeltaY;
	bool 		isHandleMouseDown;
	static void onHandleMouseEvent(MouseEvent event, Vector2D position, int id, Canvas* canvas);
    
    // The callback is invoked when the slider value changes
    SliderListener sliderListener;
    
	float  	    value;

public:
	Slider();
    
    /* Returns a number in closed range <0,1> which indicates a normalized position
     * of the handle relative to the background it slides along (0 indicates top). */
	float   getValue() const;
    
    void    onAdd() override;
    
    /* Sets color of the slider background to `color` and color of the slider handle
     * to inverse of the `color`. */
	void    setColor(Color3D color) override;
    
	void    setPosition(Vector2D position) override;
	void    setPriority(int priority) override;
	void    setSize(Vector2D size) override;
    void    setVisible(bool visible) override;
    void    setSliderListener(SliderListener callback);
	void    setHandleHeight(float height);
};

}

#endif
