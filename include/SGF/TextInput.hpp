
/********** SIMPLE GUI FRAMEWORK TEXT INPUT MODULE **********/

#ifndef _TEXTINPUT_HPP
#define _TEXTINPUT_HPP

#include <vector>
#include "SGF/Canvas.hpp"
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
    Rectangle        cursor;
	int 			 cursorIndex;
    Rectangle        field;
    bool             isFieldMouseDown;
    static const int keyBackspace;
    static const int keyLeftArrow;
    static const int keyReturn;
    static const int keyRightArrow;
    int              leftPad;
    static void      onFieldKeyboardEvent(int data, int id, Canvas* canvas);
    static void      onFieldMouseEvent(MouseEvent event, Vector2D position, int id, Canvas* canvas);
    void             updateCursor();
    
    // Contains size of each text character (ordered from left) in pixels
    std::vector<int> textCharSizes;
    
    int              vertPad;
    
public:

// TODO: Add updateCursor method, that uses findCharacterPos of sfmlText to compute W

	TextInput();
	const std::string* getContent();
    Rectangle&         getCursor();
    Rectangle&         getField();
    int                getLeftPadding() const;
    TextProperties*    getText() override;
    int                getVerticalPadding() const;
    Rectangle&         setColor(Color3D color) override;
	sgf::TextInput&	   setContent(const std::string& content);
    TextInput&         setLeftPadding(int padding);
    Rectangle&         setPosition(Vector2D position) override;
	Rectangle&         setPriority(int priority) override;
	Rectangle&         setSize(Vector2D size) override;
    Rectangle&         setText(TextProperties* properties) override;
    TextInput&         setVerticalPadding(int padding);
    Rectangle&         setVisible(bool visible) override;
};

}

#endif
