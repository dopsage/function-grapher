
#include <iostream>
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/ScrollView.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/Types.hpp"
#include "FunctionEntry.hpp"

// Colors
static const sgf::Color3D   C_BLACK ({ 0, 0, 0 });
static const sgf::Color3D   C_BLUE  ({ 0, 0, 255 });
static const sgf::Color3D   C_RED   ({ 255, 0, 0 });
static const sgf::Color3D   C_GRAY  ({ 128, 128, 128 });
static const sgf::Color3D   C_GREEN ({ 0, 255, 0 });
static const sgf::Color3D   C_WHITE ({ 255, 255, 255 });

// Layout-specific
static const float              F_CURSOR_WIDTH              (2.F);
static const float              F_FUNCTION_ENTRY_HEIGHT     (50.F);
static const float              F_SCROLL_VIEW_WIDTH         (200.F);
static const float              F_SLIDER_HANDLE_WIDTH       (25.F);
static const float              F_STATUS_BAR_HEIGHT         (50.F);
static const float              F_STATUS_MOUSE_INFO_WIDTH   (100.F);
static const float              F_STATUS_ZOOM_INFO_WIDTH    (100.F);
static const float              F_TOOLBAR_BUTTON_MARGIN     (30.F);
static const sgf::Milliseconds  MS_CURSOR_BLINK_DURATION    (250);
static const sgf::Milliseconds  MS_CANVAS_TICK_DURATION     (1000/60);
static const std::string        STR_CANVAS_TITLE            ("Function grapher");
static const sgf::Vector2D      V_CANVAS_SIZE               ({ 1280, 720 });
static const sgf::Vector2D      V_INPUT_PADDING             ({ 10, 10 });
static const sgf::Vector2D      V_TOOLBAR_BUTTON_SIZE       ({ 50, 50 });

static void onAddEntryButtonEvent   (int id, sgf::Canvas* canvas);
static void onResetGraphButtonEvent (int id, sgf::Canvas* canvas);
static void onZoomDownButtonEvent   (int id, sgf::Canvas* canvas);
static void onZoomUpButtonEvent     (int id, sgf::Canvas* canvas);

static std::deque<FunctionEntry>        feCopies;   // Deque preserves addresses!
static FunctionEntry                    fePrefab;
static std::deque<sgf::TextProperties>  feTProps;   // Deque preserves addresses!
static bool                             run;

int main()
{
    /********** CONFIGURE INSTANCES **********/
    
    sgf::TextProperties mousePositionText   = { C_BLACK, "(100, 100)", 16 };
    sgf::TextProperties zoomText            = { C_BLACK, "x1.0", 16 };
    
// TODO: make setColor of every rect make its subrects the same color
    sgf::Button     bAddEntry;
    sgf::Button     bResetGraph;
    sgf::Button     bZoomDown;
    sgf::Button     bZoomUp;
    sgf::Canvas     cCanvas;
    sgf::Rectangle  rGraphBackground;
    sgf::Rectangle  rStatusBackground;
    sgf::Rectangle  tMousePosition;
    sgf::Rectangle  tZoom;
    sgf::ScrollView svFunctions;
    sgf::VList      vlToolbarButtons;
    
    // [BUTTON] ADD ENTRY
    bAddEntry.setButtonListener(onAddEntryButtonEvent);
    bAddEntry.setColor(C_BLUE);
    bAddEntry.setMeta(&svFunctions);    // Scroll view gets updated with entries on button click
    bAddEntry.setPosition({ 0, 0 });    // Automatic (svFunctions)
    bAddEntry.setPriority(0);           // Automatic (svFunctions)
    bAddEntry.setSize({
        F_SCROLL_VIEW_WIDTH - F_SLIDER_HANDLE_WIDTH,
        F_FUNCTION_ENTRY_HEIGHT
    });
    bAddEntry.setText(nullptr);
    bAddEntry.setVisible(true);
    
    // [BUTTON] RESET GRAPH
    bResetGraph.setButtonListener(onResetGraphButtonEvent);
    bResetGraph.setColor(C_BLUE);
    bResetGraph.setMeta(nullptr);
    bResetGraph.setPosition({ 0, 0 });  // Automatic (vlToolbarButtons)
    bResetGraph.setPriority(0);         // Automatic (vlToolbarButtons)
    bResetGraph.setSize(V_TOOLBAR_BUTTON_SIZE);
    bResetGraph.setText(nullptr);
    bResetGraph.setVisible(true);
    
    // [BUTTON] ZOOM DOWN
    bZoomDown.copy(&bResetGraph);
    bZoomDown.setColor(C_GREEN);
    bZoomDown.setButtonListener(onZoomDownButtonEvent);
    
    // [BUTTON] ZOOM UP
    bZoomUp.copy(&bResetGraph);
    bZoomUp.setColor(C_RED);
    bZoomUp.setButtonListener(onZoomUpButtonEvent);
    
    // [CANVAS] CANVAS
// TODO: Make the main loop not busy-wait for the next frame, cpu is being wasted!
// TODO: Solve the problem with removal of text-assigned rectangle (in remove method)
//       recons: Just try adding FEs using the button and inputting their indices in them,
//       then look what happens to the ones beneath the removed one! it cannot be like tha!
//       this sometimes produces segfaults too, probably textprops mismatch.
    cCanvas.setPosition({ 1920 - V_CANVAS_SIZE.x, 1080 - V_CANVAS_SIZE.y });    // For testing
    cCanvas.setSize(V_CANVAS_SIZE);
    cCanvas.setTickDuration(MS_CANVAS_TICK_DURATION);
    cCanvas.setTitle(STR_CANVAS_TITLE);
    
    // [RECTANGLE] GRAPH BACKGROUND
    rGraphBackground.setColor(C_WHITE);
    rGraphBackground.setMeta(nullptr);
    rGraphBackground.setPosition({ F_SCROLL_VIEW_WIDTH, 0 });
    rGraphBackground.setPriority(0); 
    rGraphBackground.setSize({
        V_CANVAS_SIZE.x - F_SCROLL_VIEW_WIDTH,
        V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT
    });
    
    // [RECTANGLE] STATUS BACKGROUND
    rStatusBackground.setColor(C_GRAY);
    rStatusBackground.setMeta(nullptr);
    rStatusBackground.setPosition({
        0,
        V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT
    });
    rStatusBackground.setPriority(2); 
    rStatusBackground.setSize({
        V_CANVAS_SIZE.x,
        F_STATUS_BAR_HEIGHT
    });
    
    // [TEXT] MOUSE POSITION
    tMousePosition.setColor(C_GRAY);
    tMousePosition.setMeta(nullptr);
    tMousePosition.setPosition({
        V_CANVAS_SIZE.x - F_STATUS_ZOOM_INFO_WIDTH - F_STATUS_MOUSE_INFO_WIDTH,
        V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT
    });
    tMousePosition.setPriority(3); 
    tMousePosition.setSize({ F_STATUS_MOUSE_INFO_WIDTH, F_STATUS_BAR_HEIGHT });
    tMousePosition.setText(&mousePositionText);
    tMousePosition.setVisible(true);
    
    // [TEXT] ZOOM
    tZoom.copy(&tMousePosition);
    tZoom.setPosition({
        tZoom.getX() + F_STATUS_MOUSE_INFO_WIDTH,
        tZoom.getY()
    });
    tZoom.setText(&zoomText);
    
    // [FUNCTION ENTRY] FUNCTION ENTRY PREFAB
// TODO: Make setText calls direct, so there is no need to dig deep (like below to getField).
    fePrefab.setColor(C_GREEN);
    fePrefab.setParentList(&svFunctions.getList());
    fePrefab.setMeta(nullptr);
    fePrefab.setPosition({ 0, 0 });     // Automatic (svFunctions.getList)
    fePrefab.setPriority(0);            // Automatic (svFunctions.getList)
    fePrefab.setSize(bAddEntry.getSize());
    fePrefab.setText(nullptr);
    fePrefab.setVisible(true);
    fePrefab.getButton().setColor(C_RED);
    fePrefab.getTextInput().setBlinkDuration(MS_CURSOR_BLINK_DURATION);
    fePrefab.getTextInput().setColor(C_BLUE);
    fePrefab.getTextInput().setCursorWidth(F_CURSOR_WIDTH);
    fePrefab.getTextInput().setFilter(sgf::InputFilter::MATH);
    fePrefab.getTextInput().setLeftPadding(V_INPUT_PADDING.x);
    fePrefab.getTextInput().setVerticalPadding(V_INPUT_PADDING.y);
    fePrefab.getTextInput().getField().setText(nullptr);    // Prefab variable, needs setting
    fePrefab.getTextInput().getCursor().setColor(C_BLACK);
    fePrefab.getTextInput().getField().setColor(C_BLUE);
    
    // [SCROLL VIEW] FUNCTIONS
// TODO: add getSlider for customization
    svFunctions.setColor(C_RED);
    svFunctions.setMeta(nullptr);
    svFunctions.setPosition({ 0, 0 });
    svFunctions.setPriority(1);
    svFunctions.setSize({
        F_SCROLL_VIEW_WIDTH,
        V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT
    });
    svFunctions.setSliderWidth(F_SLIDER_HANDLE_WIDTH);
    svFunctions.setText(nullptr);
    svFunctions.setVisible(true);
    svFunctions.getList().insert(0, &bAddEntry);
    
    // [VERTICAL LIST] TOOLBAR BUTTONS
    vlToolbarButtons.setColor(C_WHITE);
    vlToolbarButtons.setPosition({
        V_CANVAS_SIZE.x - 1 * V_TOOLBAR_BUTTON_SIZE.x - F_TOOLBAR_BUTTON_MARGIN,
        V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT - 3 * V_TOOLBAR_BUTTON_SIZE.y - F_TOOLBAR_BUTTON_MARGIN
    });
    vlToolbarButtons.setPriority(1);
    vlToolbarButtons.setSize({ V_TOOLBAR_BUTTON_SIZE.x, 3 * V_TOOLBAR_BUTTON_SIZE.y });
    vlToolbarButtons.setText(nullptr);
    vlToolbarButtons.setVisible(true);
    vlToolbarButtons.insert(0, &bZoomUp);
    vlToolbarButtons.insert(1, &bZoomDown);
    vlToolbarButtons.insert(2, &bResetGraph);
    
    /********** RUN THE FUNCTION GRAPHER APPLICATION **********/    
    
    cCanvas.add(bAddEntry);
    cCanvas.add(rGraphBackground);
    cCanvas.add(rStatusBackground);
    cCanvas.add(tMousePosition);
    cCanvas.add(tZoom);
    cCanvas.add(svFunctions);
    cCanvas.add(vlToolbarButtons);
    
    run = true;
    while(cCanvas.alive())
    {
        if(cCanvas.tick())
        {
            if(!run) cCanvas.kill();
            
            // Do updates ...
        }
    }
    
    return 0;
}

static void onAddEntryButtonEvent(int id, sgf::Canvas* canvas)
{
    sgf::ScrollView* svFunctions = (sgf::ScrollView*)canvas->getRectangle(id)->getMeta();
    std::cout << "Add entry " << svFunctions->getList().getCount() << std::endl;
    
    /* Add a new function entry instance together with text properties that are bound
     * to it. The entry is a copy of the function entry prefab. */
    feCopies.push_back(FunctionEntry());
    feTProps.push_back({ C_BLACK, "", 16 });
    feCopies.back().copy(&fePrefab);
    feCopies.back().getTextInput().getField().setText(&feTProps.back());
    
    svFunctions->getList().insert(svFunctions->getList().getCount() - 1, &feCopies.back());
}

static void onResetGraphButtonEvent(int id, sgf::Canvas* canvas)
{
    std::cout << "Reset graph" << std::endl;
}
static void onZoomDownButtonEvent(int id, sgf::Canvas* canvas)
{
    std::cout << "Zoom down" << std::endl;
}

static void onZoomUpButtonEvent(int id, sgf::Canvas* canvas)
{
    std::cout << "Zoom up" << std::endl;
}
