
#ifndef _FUNCTIONENTRY_HPP
#define _FUNCTIONENTRY_HPP

#include <string>
#include "SGF/Button.hpp"
#include "SGF/Canvas.hpp"
#include "SGF/FunctionProperties.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/VList.hpp"

/* DESC */
class FunctionEntry : public sgf::Rectangle
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

#endif
