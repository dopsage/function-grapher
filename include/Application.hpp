
#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#include <iostream>
#include "SGF/Button.hpp"
#include "SGF/Canvas.hpp"
#include "SGF/FunctionGrapher.hpp"
#include "SGF/ScrollView.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/VList.hpp"
#include "SGF/VSlider.hpp"
#include "FunctionEntry.hpp"

class Application final
{
private:
    static const sgf::Color3D       C_BLACK;
    static const sgf::Color3D       C_BLUE;
    static const sgf::Color3D       C_RED;
    static const sgf::Color3D       C_GRAY;
    static const sgf::Color3D       C_GREEN;
    static const sgf::Color3D       C_WHITE;
    static const float              F_CURSOR_WIDTH;
    static const float              F_FUNCTION_ENTRY_HEIGHT;
    static const float              F_SCROLL_VIEW_WIDTH;
    static const float              F_SLIDER_HANDLE_HEIGHT;
    static const float              F_SLIDER_WIDTH;
    static const float              F_STATUS_BAR_HEIGHT;
    static const float              F_STATUS_MOUSE_INFO_WIDTH;
    static const float              F_STATUS_ZOOM_INFO_WIDTH;
    static const float              F_TOOLBAR_BUTTON_MARGIN;
    static const float              F_VIEW_DEFAULT_END_X;
    static const float              F_VIEW_DEFAULT_START_X;
    static const float              F_VIEW_DEFAULT_START_Y;
    static const int                I_CANVAS_DRAW_RATE;
    static const int                I_ENTRY_TEXT_SIZE;
    static const int                I_STATUS_TEXT_SIZE;
    static const sgf::milliseconds  MS_CURSOR_BLINK_DURATION;
    static const std::string        STR_CANVAS_TITLE;
    static const sgf::Vector2D      V_CANVAS_SIZE;
    static const sgf::Vector2D      V_TEXT_INPUT_PADDING;
    static const sgf::Vector2D      V_TOOLBAR_BUTTON_SIZE;

    static bool                     isViewMouseDown;
    static FunctionEntry            fePrefab;
    static sgf::Vector2D            mouseDragStart;
    static sgf::TextProperties      tpPrefab;
    static sgf::Vector2D            viewChange;
    static float                    viewEndX;
    static float                    viewStartX;
    static float                    viewStartY;
    static float                    zoomScale;
    
    static void                     onAddEntryButtonEvent   (sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr);
    static void                     onEntryTextInputEvent   (std::wstring content, sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr);
    static void                     onGraphsViewMouseEvent  (sgf::MouseEvent event, sgf::Vector2D position, sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr);
    static void                     onRemoveEntryButtonEvent(sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr);
    static void                     onResetViewButtonEvent  (sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr);
    static void                     onZoomInButtonEvent     (sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr);
    static void                     onZoomOutButtonEvent    (sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr);
    void                            configureInstances      ();
    void                            freeUsedResources       ();

    sgf::Button                     bAddEntry;
    sgf::Button                     bResetGraph;
    sgf::Button                     bZoomIn;
    sgf::Button                     bZoomOut;
    sgf::Canvas                     canvas;
    sgf::FunctionGrapher            fgGraphsView;
    sgf::Rectangle                  rStatusBackground;
    sgf::Rectangle                  rMousePosition;
    sgf::Rectangle                  rZoom;
    sgf::ScrollView                 svFunctions;
    sgf::TextProperties             tMousePosition;
    sgf::TextProperties             tZoom;
    sgf::VList                      vlToolbarButtons;

public:
    Application();
    ~Application();
    int run();
};

#endif

