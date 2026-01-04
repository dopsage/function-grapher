
#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

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
    static const int                I_CANVAS_DRAW_RATE;
    static const int                I_ENTRY_TEXT_SIZE;
    static const int                I_STATUS_TEXT_SIZE;
    static const sgf::Milliseconds  MS_CURSOR_BLINK_DURATION;
    static const std::string        STR_CANVAS_TITLE;
    static const sgf::Vector2D      V_CANVAS_SIZE;
    static const sgf::Vector2D      V_TEXT_INPUT_PADDING;
    static const sgf::Vector2D      V_TOOLBAR_BUTTON_SIZE;
    static FunctionEntry            fePrefab;
    static sgf::TextProperties      tpPrefab;
    static void                     onAddEntryButtonEvent   (int rectangleId, sgf::Canvas* canvasPtr);
    static void                     onEntryTextInputEvent   (std::wstring content, int rectangleId, sgf::Canvas* canvasPtr);
    static void                     onRemoveEntryButtonEvent(int rectangleId, sgf::Canvas* canvasPtr);
    static void                     onResetGraphButtonEvent (int rectangleId, sgf::Canvas* canvasPtr);
    static void                     onZoomInButtonEvent     (int rectangleId, sgf::Canvas* canvasPtr);
    static void                     onZoomOutButtonEvent    (int rectangleId, sgf::Canvas* canvasPtr);
    void                            configureInstances      ();
    void                            freeUsedResources       ();
    sgf::Button                     bAddEntry;
    sgf::Button                     bResetGraph;
    sgf::Button                     bZoomIn;
    sgf::Button                     bZoomOut;
    sgf::Canvas                     canvas;
    sgf::Rectangle                  rGraphBackground;
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

