
#ifndef _FUNCTIONENTRY_HPP
#define _FUNCTIONENTRY_HPP

#include <string>
#include "SGF/Button.hpp"
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/VList.hpp"

struct FunctionData
{
    std::string name;
    float (*definition)(float);
};

class FunctionEntry : public sgf::Rectangle
{
private:
    sgf::Button         button;
    sgf::TextInput      input;
    static void         onButtonEvent(int id, sgf::Canvas* canvas);
    sgf::VList*         parentList;

public:
    FunctionEntry();
    void                    copy(sgf::Rectangle* other) override;
    FunctionData            getData() const;
    sgf::VList&             getParentList();
    sgf::TextProperties*    getText();
    sgf::Button&            getButton();
    sgf::TextInput&         getTextInput();
    bool            isValid() const;
    void            onAdd() override;
    void            onRemove() override;
    void            setColor(sgf::Color3D color) override;
    void            setParentList(sgf::VList* list);
    void            setPosition(sgf::Vector2D position) override;
    void            setPriority(int priority) override;
    void            setSize(sgf::Vector2D size) override;
    void            setText(sgf::TextProperties* properties) override;
    void            setVisible(bool visible) override;
};

#endif
