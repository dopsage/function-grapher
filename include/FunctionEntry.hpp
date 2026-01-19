
#ifndef _FUNCTIONENTRY_HPP
#define _FUNCTIONENTRY_HPP

#include <string>

#include "SGF/Button.hpp"
#include "SGF/Canvas.hpp"
#include "SGF/FunctionProperties.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/VList.hpp"

/* Application-specific component that lets a user to input a math expression
 * through TextInput instance. There is also a Button instance placed on
 * the right of the input that may be customized to perform desired behaviour.
 * In case of this application, the button serves as self-destructor - it removes
 * the whole entry from list of them on click event. */
class FunctionEntry final : public sgf::Rectangle
{
private:
    sgf::Button             button;
    sgf::FunctionProperties function;
    sgf::TextInput          input;
    static void             onTextInputEvent(std::wstring content, sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr);

public:
    FunctionEntry();
    void                        copy(sgf::Rectangle* other)                     override;
    sgf::Button*                getButtonPtr();
    sgf::FunctionProperties*    getFunction();
    sgf::TextInput*             getTextInputPtr();
    void                        onAdd()                                         override;
    void                        onRemove()                                      override;
    void                        setButtonListener(sgf::ButtonListener listener);
    void                        setButtonWidth(float width);
    void                        setPosition(sgf::Vector2D position)             override;
    void                        setPriority(int priority)                       override;
    void                        setSize(sgf::Vector2D size)                     override;
    void                        setVisible(bool visible)                        override;
};

#endif	// _FUNCTIONENTRY_HPP
