
/********** SIMPLE GUI FRAMEWORK SLIDER MODULE **********/

#ifndef _SLIDER_HPP
#define _SLIDER_HPP

#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

// Derived properties are used as slider background, internally handle is also stored.
class Slider final : public Rectangle
{
private:
	Rectangle   handle;
	float 		handleDeltaY;
	bool 		isHandleMouseDown;
	float  	    value;
	
	// this payload thing is brilliant!
	static void onHandleMouseEvent(MouseEvent event, Vector2D position, void* payload);

public:
	static const float HANDLE_HEIGHT;

	Slider();
	const Rectangle& getHandle() const;
	float 	   		 getValue() const;
	Rectangle& 		 setColor(Color3D color) override;
	Rectangle& 		 setPosition(Vector2D position) override;
	Rectangle& 		 setPriority(int priority) override;
	Rectangle& 		 setSize(Vector2D size) override;
	void 	   		 setHandleHeight(float height);
};

}

#endif
