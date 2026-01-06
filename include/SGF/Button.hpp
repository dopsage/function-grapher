
/********** SIMPLE GUI FRAMEWORK BUTTON MODULE **********/

#ifndef _BUTTON_HPP
#define _BUTTON_HPP

#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Provides a primitive button functionality. Allows listening for clicks in bounds
 * of the button rectangular area. */
class Button final : public Rectangle
{
private:
    bool        isMouseDown;
	static void onButtonMouseEvent(MouseEvent event, Vector2D position, Rectangle* instancePtr, Canvas* canvasPtr);
    
    /* The callback is invoked when the button receives mouse up event while the
     * mouse is in the buttons rectangular area. */
    ButtonListener listener;

public:
	Button();
    void            copy(Rectangle* other)  override;
    ButtonListener  getListener()           const;
    void            setListener(ButtonListener callback);
};

}

#endif
