
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
class TextInput final : public Rectangle
{
private:
    Milliseconds        blinkDuration;
    Rectangle           cursor;
	int 			    cursorIndex;
    Rectangle           field;
    bool                isFieldMouseDown;
    static const int    keyBackspace;
    static const int    keyLeftArrow;
    static const int    keyReturn;
    static const int    keyRightArrow;
    bool                isSelected;
    Milliseconds        lastBlinkTime;
    int                 lastTextSize;
    int                 leftPad;
    static void         onFieldKeyboardEvent(int data, int id, Canvas* canvas);
    static void         onFieldMouseEvent(MouseEvent event, Vector2D position, int id, Canvas* canvas);
    void                updateCursor();
    
    // Contains size of each text character (ordered from left) in pixels
    std::vector<float> textCharSizes;
    
    int                 vertPad;
    
public:
	TextInput();
	const std::string*  getContent();
    Rectangle&          getField();
    int                 getLeftPadding() const;
    TextProperties*     getText() override;
    int                 getVerticalPadding() const;
    void                onAdd() override;
    void                onTick(int tickIndex) override;
    void                setBlinkDuration(Milliseconds duration);
    void                setColor(Color3D color) override;
	void	            setContent(const std::string& content);
    void                setCursorWidth(int width);
    void                setLeftPadding(int padding);
    void                setPosition(Vector2D position) override;
	void                setPriority(int priority) override;
	void                setSize(Vector2D size) override;
    void                setText(TextProperties* properties) override;
    void                setVerticalPadding(int padding);
    void                setVisible(bool visible) override;
};

}

#endif
