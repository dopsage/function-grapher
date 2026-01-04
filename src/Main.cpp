
#include <iostream>
#include "SGF/Button.hpp"
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/ScrollView.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/TextProperties.hpp"
#include "SGF/Types.hpp"
#include "SGF/VList.hpp"
#include "SGF/VSlider.hpp"
#include "FunctionEntry.hpp"

static const sgf::Color3D       C_BLACK ({ 0x00, 0x00, 0x00 });
static const sgf::Color3D       C_BLUE  ({ 0x00, 0x00, 0xff });
static const sgf::Color3D       C_RED   ({ 0xff, 0x00, 0x00 });
static const sgf::Color3D       C_GRAY  ({ 0x80, 0x80, 0x80 });
static const sgf::Color3D       C_GREEN ({ 0x00, 0xff, 0x00 });
static const sgf::Color3D       C_WHITE ({ 0xff, 0xff, 0xff });
static const float              F_CURSOR_WIDTH              (2.0f);
static const float              F_FUNCTION_ENTRY_HEIGHT     (50.0f);
static const float              F_SCROLL_VIEW_WIDTH         (300.0f);
static const float              F_SLIDER_HANDLE_HEIGHT      (50.0f);
static const float              F_SLIDER_WIDTH              (25.0f);
static const float              F_STATUS_BAR_HEIGHT         (50.0f);
static const float              F_STATUS_MOUSE_INFO_WIDTH   (100.0f);
static const float              F_STATUS_ZOOM_INFO_WIDTH    (100.0f);
static const float              F_TOOLBAR_BUTTON_MARGIN     (30.0f);
static const int                I_CANVAS_DRAW_RATE          (60);
static const int                I_ENTRY_TEXT_SIZE           (24);
static const int                I_STATUS_TEXT_SIZE          (16);
static const sgf::Milliseconds  MS_CURSOR_BLINK_DURATION    (250);
static const std::string        STR_CANVAS_TITLE            ("Function grapher");
static const sgf::Vector2D      V_CANVAS_SIZE               ({ 1280, 720 });
static const sgf::Vector2D      V_TEXT_INPUT_PADDING        ({ 10, 10 });
static const sgf::Vector2D      V_TOOLBAR_BUTTON_SIZE       ({ 50, 50 });

static void onAddEntryButtonEvent   (int rectangleId, sgf::Canvas* canvasPtr);
static void onEntryTextInputEvent   (std::wstring content, int rectangleId, sgf::Canvas* canvasPtr);
static void onRemoveEntryButtonEvent(int rectangleId, sgf::Canvas* canvasPtr);
static void onResetGraphButtonEvent (int rectangleId, sgf::Canvas* canvasPtr);
static void onZoomDownButtonEvent   (int rectangleId, sgf::Canvas* canvasPtr);
static void onZoomUpButtonEvent     (int rectangleId, sgf::Canvas* canvasPtr);

static FunctionEntry        fePrefab;
static sgf::TextProperties  tpPrefab(C_BLACK, L"", I_ENTRY_TEXT_SIZE);
static bool                 run;

int main()
{    
    /********** CONFIGURE INSTANCES **********/
    
    sgf::Button         bAddEntry;
    sgf::Button         bResetGraph;
    sgf::Button         bZoomDown;
    sgf::Button         bZoomUp;
    sgf::Canvas         canvas;
    sgf::Rectangle      rGraphBackground;
    sgf::Rectangle      rStatusBackground;
    sgf::Rectangle      rMousePosition;
    sgf::Rectangle      rZoom;
    sgf::ScrollView     svFunctions;
    sgf::TextProperties tMousePosition  (C_BLACK, L"(100, 100)", I_STATUS_TEXT_SIZE);
    sgf::TextProperties tZoom           (C_BLACK, L"x1.0",       I_STATUS_TEXT_SIZE);
    sgf::VList          vlToolbarButtons;
    
    bAddEntry.setColor      (C_GREEN);
    bAddEntry.setListener   (onAddEntryButtonEvent);
    bAddEntry.setMetaPtr    (&svFunctions);     // Scroll view gets updated on click
    bAddEntry.setSize       ({ F_SCROLL_VIEW_WIDTH - F_SLIDER_WIDTH, F_FUNCTION_ENTRY_HEIGHT });
    
    bResetGraph.setColor    (C_BLUE);
    bResetGraph.setListener (onResetGraphButtonEvent);
    bResetGraph.setSize     (V_TOOLBAR_BUTTON_SIZE);

    bZoomDown.setColor      (C_GREEN);
    bZoomDown.setListener   (onZoomDownButtonEvent);
    bZoomDown.setSize       (V_TOOLBAR_BUTTON_SIZE);
    
    bZoomUp.setColor    (C_RED);
    bZoomUp.setListener (onZoomUpButtonEvent);
    bZoomUp.setSize     (V_TOOLBAR_BUTTON_SIZE);
    
    canvas.setDrawingRate   (I_CANVAS_DRAW_RATE);
    canvas.setPosition      ({ 1920 - V_CANVAS_SIZE.x, 1080 - V_CANVAS_SIZE.y });
    canvas.setSize          (V_CANVAS_SIZE);
    canvas.setTitle         (STR_CANVAS_TITLE);

    fePrefab.setButtonListener  (onRemoveEntryButtonEvent);
    fePrefab.setButtonWidth     (F_FUNCTION_ENTRY_HEIGHT);
    fePrefab.setSize            ({ F_SCROLL_VIEW_WIDTH - F_SLIDER_WIDTH, F_FUNCTION_ENTRY_HEIGHT });
    fePrefab.getButtonPtr()->setColor   (C_BLACK);
    fePrefab.getButtonPtr()->setMetaPtr (&fePrefab);                            // Prefab variable (entry pointer)
    fePrefab.getTextInputPtr()->setBlinkDuration    (MS_CURSOR_BLINK_DURATION);
    fePrefab.getTextInputPtr()->setColor            (C_BLUE);
    fePrefab.getTextInputPtr()->setCursorWidth      (F_CURSOR_WIDTH);
    fePrefab.getTextInputPtr()->setFieldText        (nullptr);                  // Prefab variable
    fePrefab.getTextInputPtr()->setFilterPtr        (&sgf::IF_ALL);
    fePrefab.getTextInputPtr()->setLeftPadding      (V_TEXT_INPUT_PADDING.x);
    fePrefab.getTextInputPtr()->setListener         (onEntryTextInputEvent);
    fePrefab.getTextInputPtr()->setVerticalPadding  (V_TEXT_INPUT_PADDING.y);
    fePrefab.getTextInputPtr()->getCursorPtr()->setColor(C_BLACK);
    fePrefab.getTextInputPtr()->getFieldPtr()->setColor (C_RED);

    rGraphBackground.setColor   (C_WHITE);
    rGraphBackground.setPosition({ F_SCROLL_VIEW_WIDTH, 0 });
    rGraphBackground.setPriority(0);
    rGraphBackground.setSize    ({ V_CANVAS_SIZE.x - F_SCROLL_VIEW_WIDTH, V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT });
    
    rStatusBackground.setColor      (C_GRAY);
    rStatusBackground.setPosition   ({ 0, V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT });
    rStatusBackground.setPriority   (5);
    rStatusBackground.setSize       ({ V_CANVAS_SIZE.x, F_STATUS_BAR_HEIGHT });
    
    rMousePosition.setColor     (C_GRAY);
    rMousePosition.setPosition  ({  V_CANVAS_SIZE.x - F_STATUS_ZOOM_INFO_WIDTH - F_STATUS_MOUSE_INFO_WIDTH,
                                    V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT });
    rMousePosition.setPriority  (6); 
    rMousePosition.setSize      ({ F_STATUS_MOUSE_INFO_WIDTH, F_STATUS_BAR_HEIGHT });
    rMousePosition.setText      (&tMousePosition);
    
    rZoom.copy          (&rMousePosition);
    rZoom.setPosition   ({ rZoom.getX() + F_STATUS_MOUSE_INFO_WIDTH, rZoom.getY() });
    rZoom.setText       (&tZoom);
    
    svFunctions.setColor        (C_GRAY);
    svFunctions.setPriority     (0);
    svFunctions.setSize         ({ F_SCROLL_VIEW_WIDTH, V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT });
    svFunctions.setSliderWidth  (F_SLIDER_WIDTH);
    svFunctions.getSliderPtr()->setColor        (C_BLUE);
    svFunctions.getSliderPtr()->setHandleHeight (F_SLIDER_HANDLE_HEIGHT);
    svFunctions.getSliderPtr()->getHandlePtr()->setColor(C_WHITE);
    
    vlToolbarButtons.setPosition({  V_CANVAS_SIZE.x - 1 * V_TOOLBAR_BUTTON_SIZE.x - F_TOOLBAR_BUTTON_MARGIN,
                                    V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT - 3 * V_TOOLBAR_BUTTON_SIZE.y - F_TOOLBAR_BUTTON_MARGIN });
    vlToolbarButtons.setPriority(1);
    
    /********** RUN THE FUNCTION GRAPHER APPLICATION **********/    
    
    svFunctions.getListPtr()->push(&bAddEntry);
    vlToolbarButtons.push(&bZoomUp);
    vlToolbarButtons.push(&bZoomDown);
    vlToolbarButtons.push(&bResetGraph);
    
    canvas.add(&bAddEntry);
    canvas.add(&bResetGraph);
    canvas.add(&bZoomDown);
    canvas.add(&bZoomUp);
    canvas.add(&rGraphBackground);
    canvas.add(&rStatusBackground);
    canvas.add(&rMousePosition);
    canvas.add(&rZoom);
    canvas.add(&svFunctions);
    canvas.add(&vlToolbarButtons);
    
    // Add 10 function entries at start by emulating add button press
    for(int i = 0; i < 10; i++)
        bAddEntry.getListener()(bAddEntry.getId(), &canvas);
    
    run = true;
    while(canvas.isActive())
    {
        if(!run)    canvas.stop();
        else        canvas.tick();
    
        // Do updates ...
    }
    
    // Should clean here, but all of this gonna be wrapped in class anyway ...
    
    return 0;
}

// Key thing to remember: do not forget about adding to canvas, VList does not do that for ya!

static void onAddEntryButtonEvent(int rectangleId, sgf::Canvas* canvasPtr)
{
    // Retrieve scroll view reference from the button metadata
    sgf::ScrollView* sv = (sgf::ScrollView*)canvasPtr->getRectanglePtr(rectangleId)->getMetaPtr();
    
    /* Instantiate function entry and text properties prefab. Heap allocation is used
     * to preserve data across entry add/remove callback calls, later the memory is
     * accessed (by digging through rectangle metadata relations) and freed. */
    FunctionEntry*          fe = new FunctionEntry();
    sgf::TextProperties*    tp = new sgf::TextProperties(tpPrefab);
    fe->copy                (&fePrefab);

    // Initialize the function entry
    fe->setMetaPtr                      (sv);   // This way button can access function entry through
    fe->getButtonPtr()->setMetaPtr      (fe);   // its metadata, and scroll view through entry's metadata
    fe->getTextInputPtr()->setFieldText (tp);

    // Add the entry to the scroll view list and then to the canvas
    sv->getListPtr()->insert(sv->getListPtr()->getCount() - 1, fe);
    canvasPtr->add(fe);
}

static void onEntryTextInputEvent(std::wstring content, int rectangleId, sgf::Canvas* canvasPtr)
{
    std::wcout << L"Text entered in " << rectangleId << L": " << content << std::endl;
}

static void onRemoveEntryButtonEvent(int rectangleId, sgf::Canvas* canvasPtr)
{
    // Retrieve entry associated with the button through its metadata, and then
    // the scroll view through the entry metadata ~ love iwt reasoning deep
    FunctionEntry*          fe = (FunctionEntry*)canvasPtr->getRectanglePtr(rectangleId)->getMetaPtr();
    sgf::TextProperties*    tp = fe->getTextInputPtr()->getFieldPtr()->getText();
    sgf::ScrollView*        sv = (sgf::ScrollView*)fe->getMetaPtr();

    // Remove the entry from the scroll view list and canvas
    sv->getListPtr()->remove(fe);
    canvasPtr->remove       (fe);
    
    // Tell the system that memory occupied by the entry and its text is now free
    delete fe;
    delete tp;
}

static void onResetGraphButtonEvent(int rectangleId, sgf::Canvas* canvasPtr)
{
    std::cout << "Reset graph" << std::endl;
}
static void onZoomDownButtonEvent(int rectangleId, sgf::Canvas* canvasPtr)
{
    std::cout << "Zoom down" << std::endl;
}

static void onZoomUpButtonEvent(int rectangleId, sgf::Canvas* canvasPtr)
{
    std::cout << "Zoom up" << std::endl;
}
