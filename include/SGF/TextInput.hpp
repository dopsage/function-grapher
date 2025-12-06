
/********** SIMPLE GUI FRAMEWORK TEXT INPUT MODULE **********/

#ifndef _TEXTINPUT_HPP
#define _TEXTINPUT_HPP

#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Provides a text input functionality with really simplistic controls. It is possible
 * to specify certain padding value of the input text, which automatically transforms
 * according to the current data. Text functions for the a class instance are completely
 * ignored, use those belonging to the input field (obtained using `getField` method). */
class TextInput : public Rectangle
{
private:
    Rectangle field;
    int       leftPad;
    int       vertPad;

public:
	TextInput();
    Rectangle&      getField();
    int             getLeftPadding() const;
    TextProperties* getText() override;
    int             getVerticalPadding() const;
    Rectangle&      setColor(Color3D color) override;
    TextInput&      setLeftPadding(int padding);
    Rectangle&      setPosition(Vector2D position) override;
	Rectangle&      setPriority(int priority) override;
	Rectangle&      setSize(Vector2D size) override;
    Rectangle&      setText(TextProperties* properties) override;
    TextInput&      setVerticalPadding(int padding);
    Rectangle&      setVisible(bool visible) override;
};

}

#endif
