
/********** SIMPLE GUI FRAMEWORK SLIDER MODULE **********/

#ifndef _SLIDER_HPP
#define _SLIDER_HPP

#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Provides a vertical slider functionality by means of two rectangles. The class
 * derives from `Rectangle` to act as the slider background, it stores a rectangle
 * instance that acts as the slider handle. */
class Slider final : public Rectangle
{
private:
	Rectangle   handle;
	float 		handleDeltaY;
	bool 		isHandleMouseDown;
	static void onHandleMouseEvent(MouseEvent event, Vector2D position, void* payload);
	float  	    value;

public:
	static const float HANDLE_HEIGHT;

	Slider();
	const Rectangle& getHandle() const;
    
    /* Returns a number in  closed range <0,1> which indicates a normalized position
     * of the handle relative to the background it slides along. */
	float 	   		 getValue() const;
    
    /* Sets color of the slider background to `color` and color of the slider handle
     * to inverse of `color`. */
	Rectangle& 		 setColor(Color3D color) override;
    
	Rectangle& 		 setPosition(Vector2D position) override;
	Rectangle& 		 setPriority(int priority) override;
	Rectangle& 		 setSize(Vector2D size) override;
	void 	   		 setHandleHeight(float height);
};

}

#endif
