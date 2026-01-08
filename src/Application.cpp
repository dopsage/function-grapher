
#include "Application.hpp"

const sgf::Color3D      Application::C_BLACK                    ({ 0x00, 0x00, 0x00 });
const sgf::Color3D      Application::C_BLUE                     ({ 0x00, 0x00, 0xff });
const sgf::Color3D      Application::C_RED                      ({ 0xff, 0x00, 0x00 });
const sgf::Color3D      Application::C_GRAY                     ({ 0x80, 0x80, 0x80 });
const sgf::Color3D      Application::C_GREEN                    ({ 0x00, 0xff, 0x00 });
const sgf::Color3D      Application::C_WHITE                    ({ 0xff, 0xff, 0xff });
const float             Application::F_CURSOR_WIDTH             (2.0f);
const float             Application::F_FUNCTION_ENTRY_HEIGHT    (50.0f);
const float             Application::F_SCROLL_VIEW_WIDTH        (300.0f);
const float             Application::F_SLIDER_HANDLE_HEIGHT     (50.0f);
const float             Application::F_SLIDER_WIDTH             (25.0f);
const float             Application::F_STATUS_BAR_HEIGHT        (50.0f);
const float             Application::F_STATUS_MOUSE_INFO_WIDTH  (140.0f);
const float             Application::F_STATUS_ZOOM_INFO_WIDTH   (100.0f);
const float             Application::F_TOOLBAR_BUTTON_MARGIN    (30.0f);
const float             Application::F_VIEW_DEFAULT_END_X       (+4.0f);
const float             Application::F_VIEW_DEFAULT_START_X     (-4.0f);
const float             Application::F_VIEW_DEFAULT_START_Y     (-2.0f);
const int               Application::I_CANVAS_DRAW_RATE         (60);
const int               Application::I_ENTRY_TEXT_SIZE          (24);
const int               Application::I_STATUS_TEXT_SIZE         (16);
const sgf::Milliseconds Application::MS_CURSOR_BLINK_DURATION   (250);
const std::string       Application::STR_CANVAS_TITLE           ("Function grapher");
const sgf::Vector2D     Application::V_CANVAS_SIZE              ({ 1280, 720 });
const sgf::Vector2D     Application::V_TEXT_INPUT_PADDING       ({ 10, 10 });
const sgf::Vector2D     Application::V_TOOLBAR_BUTTON_SIZE      ({ 50, 50 });

bool                    Application::isViewMouseDown            (false);
FunctionEntry           Application::fePrefab;
sgf::Vector2D           Application::mouseDragStart             ({ 0.0f, 0.0f });
sgf::TextProperties     Application::tpPrefab                   (C_BLACK, L"", I_ENTRY_TEXT_SIZE);
sgf::Vector2D           Application::viewChange                 ({ 0.0f, 0.0f });
float                   Application::viewEndX                   (F_VIEW_DEFAULT_END_X);
float                   Application::viewStartX                 (F_VIEW_DEFAULT_START_X);
float                   Application::viewStartY                 (F_VIEW_DEFAULT_START_Y);
float                   Application::zoomScale                  (1.0f);

void Application::onAddEntryButtonEvent(sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr)
{
    // Retrieve scroll view reference from the button metadata
    sgf::ScrollView* sv = (sgf::ScrollView*)instancePtr->getMetaPtr();
    
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

void Application::onEntryTextInputEvent(std::wstring content, sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr)
{
    std::wcout << L"Text entered in " << instancePtr->getId() << L": " << content << std::endl;
}

void Application::onGraphsViewMouseEvent(sgf::MouseEvent event, sgf::Vector2D position, sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr)
{
    sgf::FunctionGrapher*   fg  = (sgf::FunctionGrapher*)instancePtr;
    sgf::Rectangle*         m   = (sgf::Rectangle*)fg->getMetaPtr();

    if(event == sgf::MouseEvent::DOWN)
    {
        // At start, catch the dragging start position and initialize view just for safety
        mouseDragStart  = position;
        fg->setView(viewStartX, viewEndX, viewStartY);
        
        isViewMouseDown = true;
    }
    else if(event == sgf::MouseEvent::MOVE)
    {
        if(isViewMouseDown)
        {
            /* Compute the displacement relative to dragging start position, transform
             * the vector to grapher plane coordinates in order to get appropriate behaviour. */
            float ppu   = fg->getViewPtr()->pixelsPerUnit;
            viewChange  =
            {
                (mouseDragStart.x - position.x) / ppu,
                (position.y - mouseDragStart.y) / ppu
            };
            
            // Update the view by including the displacement to the current axis rangers
            fg->setView(
                viewStartX  + viewChange.x,
                viewEndX    + viewChange.x,
                viewStartY  + viewChange.y
            );
        }
        
        // Update mouse position text
        if(m->isUsingText())
        {
            sgf::Vector2D grapherMousePos = fg->toGrapherPlane(position);
            
            wchar_t buffer[32];
            swprintf(buffer, 32, L"( %.4f %.4f )", grapherMousePos.x, grapherMousePos.y);
            
            m->getText()->content      = std::wstring(buffer);
            m->getText()->refreshFlag  = true;
        }
    }
    else if(event == sgf::MouseEvent::UP)
    {
        if(isViewMouseDown)
        {
            // In the end, view arguments range and starting value with displacement
            viewStartX  += viewChange.x;
            viewEndX    += viewChange.x;
            viewStartY  += viewChange.y;
            viewChange = { 0.0f, 0.0f };
            isViewMouseDown = false;
        }
    }
    
    // This is really cool, one can integrate UI modules with the grapher :D
    //((sgf::Rectangle*)fg->getMetaPtr())->setPosition(fg->toCanvasPlane({ 3.0f, -2.0f }));
}

void Application::onRemoveEntryButtonEvent(sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr)
{
    /* Retrieve entry associated with the button through its metadata, and then
     * the scroll view through the entry metadata ~ love iwt reasoning deep.
       Note from future: actually Application pointer can be passed, but it appears dirty }: */
    FunctionEntry*          fe = (FunctionEntry*)instancePtr->getMetaPtr();
    sgf::TextProperties*    tp = fe->getTextInputPtr()->getFieldPtr()->getText();
    sgf::ScrollView*        sv = (sgf::ScrollView*)fe->getMetaPtr();

    // Remove the entry from the scroll view list and canvas
    sv->getListPtr()->remove(fe);
    canvasPtr->remove       (fe);
    
    // Tell the system that memory occupied by the entry and its text is now free
    delete fe;
    delete tp;
}

void Application::onResetViewButtonEvent(sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr)
{
    sgf::Rectangle*         z   = (sgf::Rectangle*)instancePtr->getMetaPtr();
    sgf::FunctionGrapher*   fg  = (sgf::FunctionGrapher*)z->getMetaPtr();

    viewStartX  = F_VIEW_DEFAULT_START_X;
    viewEndX    = F_VIEW_DEFAULT_END_X;
    viewStartY  = F_VIEW_DEFAULT_START_Y;
    zoomScale   = 1.0f;
    
    fg->setView(viewStartX, viewEndX, viewStartY);
    
    // Update zoom text
    wchar_t buffer[16];
    swprintf(buffer, 16, L"x%.4f", zoomScale);
    z->getText()->content      = std::wstring(buffer);
    z->getText()->refreshFlag  = true;
}

void Application::onZoomInButtonEvent(sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr)
{
    sgf::Rectangle*         z   = (sgf::Rectangle*)instancePtr->getMetaPtr();
    sgf::FunctionGrapher*   fg  = (sgf::FunctionGrapher*)z->getMetaPtr();

    float quarterViewLength = (viewEndX - viewStartX) / 4.0f;
    viewStartX  += quarterViewLength;
    viewEndX    -= quarterViewLength;
    
    /* Since view is not yet updated, by means of property of saved proportions
     * between width and height of the view, it is possible to obtain future view
     * height which is half of the old one. */
    viewStartY  += (fg->getViewPtr()->vE - fg->getViewPtr()->vS) / 2.0f / 2.0f;
    
    zoomScale   *= 2.0f;
    fg->setView(viewStartX, viewEndX, viewStartY);
    
    // Update zoom text
    wchar_t buffer[16];
    swprintf(buffer, 16, L"x%.4f", zoomScale);
    z->getText()->content      = std::wstring(buffer);
    z->getText()->refreshFlag  = true;
}

void Application::onZoomOutButtonEvent(sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr)
{
    sgf::Rectangle*         z   = (sgf::Rectangle*)instancePtr->getMetaPtr();
    sgf::FunctionGrapher*   fg  = (sgf::FunctionGrapher*)z->getMetaPtr();

    float halfViewLength = (viewEndX - viewStartX) / 2.0f;
    viewStartX  -= halfViewLength;
    viewEndX    += halfViewLength;
    viewStartY  -= (fg->getViewPtr()->vE - fg->getViewPtr()->vS) / 2.0f;
    zoomScale   /= 2.0f;
    fg->setView(viewStartX, viewEndX, viewStartY);
    
    // Update zoom text
    wchar_t buffer[16];
    swprintf(buffer, 16, L"x%.4f", zoomScale);
    z->getText()->content      = std::wstring(buffer);
    z->getText()->refreshFlag  = true;
}

void Application::configureInstances()
{
    // Add function entry (button)
    bAddEntry.setColor      (C_GREEN);
    bAddEntry.setListener   (onAddEntryButtonEvent);
    bAddEntry.setMetaPtr    (&svFunctions);     // Scroll view gets updated on click
    bAddEntry.setSize       ({ F_SCROLL_VIEW_WIDTH - F_SLIDER_WIDTH, F_FUNCTION_ENTRY_HEIGHT });
    
    // Reset graph view (button)
    bResetGraph.setColor    (C_BLUE);
    bResetGraph.setListener (onResetViewButtonEvent);
    bResetGraph.setMetaPtr  (&rZoom);
    bResetGraph.setSize     (V_TOOLBAR_BUTTON_SIZE);

    // Zoom graph view in (button)
    bZoomIn.copy            (&bResetGraph);
    bZoomIn.setMetaPtr      (&rZoom);
    bZoomIn.setColor        (C_RED);
    bZoomIn.setListener     (onZoomInButtonEvent);

    // Zoom graph view out (button)
    bZoomOut.copy           (&bResetGraph);
    bZoomOut.setColor       (C_GREEN);
    bZoomOut.setListener    (onZoomOutButtonEvent);
    
    // Main window (canvas)
    canvas.setDrawingRate   (I_CANVAS_DRAW_RATE);
    canvas.setPosition      ({ 1920 - V_CANVAS_SIZE.x, 1080 - V_CANVAS_SIZE.y });
    canvas.setSize          (V_CANVAS_SIZE);
    canvas.setTitle         (STR_CANVAS_TITLE);

    // Scroll view list function entry prefab (function entry)
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
    
    // Test of custom look using context graphics, each prefab instance will do the same!
    fePrefab.getTextInputPtr()->getFieldPtr()->setContextListener([](sgf::Context* contextPtr, sgf::Rectangle* instancePtr, sgf::Canvas* canvasPtr)
    {
        sgf::Rectangle* r = (sgf::Rectangle*)instancePtr;
        
        contextPtr->line(
            r->getPosition(),
            { r->getX() + r->getWidth(), r->getY() + r->getHeight() },
            C_WHITE,
            instancePtr->getId() % 8 + 1
        );
    });

    // Graph view background (rectangle)
    fgGraphsView.setColor           (C_WHITE);
    fgGraphsView.setMetaPtr         (&rMousePosition);
    fgGraphsView.setMouseListener   (onGraphsViewMouseEvent);
    fgGraphsView.setPosition        ({ F_SCROLL_VIEW_WIDTH, 0 });
    fgGraphsView.setPriority        (0);
    fgGraphsView.setSize            ({ V_CANVAS_SIZE.x - F_SCROLL_VIEW_WIDTH, V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT });
    
    // Bottom status bar background (rectangle)
    rStatusBackground.setColor      (C_GRAY);
    rStatusBackground.setPosition   ({ 0, V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT });
    rStatusBackground.setPriority   (5);
    rStatusBackground.setSize       ({ V_CANVAS_SIZE.x, F_STATUS_BAR_HEIGHT });
    
    // Graph mouse position status text (rectangle)
    rMousePosition.setColor     (C_GRAY);
    rMousePosition.setMetaPtr   (&rZoom);
    rMousePosition.setPosition  ({  V_CANVAS_SIZE.x - F_STATUS_ZOOM_INFO_WIDTH - F_STATUS_MOUSE_INFO_WIDTH,
                                    V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT });
    rMousePosition.setPriority  (6); 
    rMousePosition.setSize      ({ F_STATUS_MOUSE_INFO_WIDTH, F_STATUS_BAR_HEIGHT });
    rMousePosition.setText      (&tMousePosition);
    
    // Graph zoom scale status text (rectangle)
    rZoom.copy          (&rMousePosition);
    rZoom.setMetaPtr    (&fgGraphsView);
    rZoom.setPosition   ({ rZoom.getX() + F_STATUS_MOUSE_INFO_WIDTH, rZoom.getY() });
    rZoom.setText       (&tZoom);
    
    // Scrollable view of added function entries (scroll view)
    svFunctions.setColor        (C_GRAY);
    svFunctions.setPriority     (0);
    svFunctions.setSize         ({ F_SCROLL_VIEW_WIDTH, V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT });
    svFunctions.setSliderWidth  (F_SLIDER_WIDTH);
    svFunctions.getSliderPtr()->setColor        (C_BLUE);
    svFunctions.getSliderPtr()->setHandleHeight (F_SLIDER_HANDLE_HEIGHT);
    svFunctions.getSliderPtr()->getHandlePtr()->setColor(C_WHITE);
    
    // Vertical list of graph manipulation buttons (vertical list)
    vlToolbarButtons.setPosition({  V_CANVAS_SIZE.x - 1 * V_TOOLBAR_BUTTON_SIZE.x - F_TOOLBAR_BUTTON_MARGIN,
                                    V_CANVAS_SIZE.y - F_STATUS_BAR_HEIGHT - 3 * V_TOOLBAR_BUTTON_SIZE.y - F_TOOLBAR_BUTTON_MARGIN });
    vlToolbarButtons.setPriority(1);
}

void Application::freeUsedResources()
{
    /* Iterate through all scroll view list function entries and emulate removal
     * button click which triggers actions that free memory allocated on heap.
     * Notice: last list member is actually a button, so it can be skipped. */
    int     entryCount = svFunctions.getListPtr()->getCount();
    while(--entryCount)
    {
        FunctionEntry* fe = (FunctionEntry*)svFunctions.getListPtr()->getMemberPtr(0);
        fe->getButtonPtr()->getListener()(fe->getButtonPtr(), &canvas);
    }
}

Application::   Application() :
                tMousePosition  (C_BLACK, L"( 0, 0 )", I_STATUS_TEXT_SIZE),
                tZoom           (C_BLACK, L"x1.0000", I_STATUS_TEXT_SIZE)
{
    configureInstances();
}

Application::~Application()
{
    freeUsedResources();
}

int Application::run()
{
    // Prepare containers
    svFunctions.getListPtr()->push(&bAddEntry);
    vlToolbarButtons.push(&bZoomIn);
    vlToolbarButtons.push(&bZoomOut);
    vlToolbarButtons.push(&bResetGraph);
    
    // Register rectangles to canvas
    canvas.add(&bAddEntry);
    canvas.add(&bResetGraph);
    canvas.add(&bZoomIn);
    canvas.add(&bZoomOut);
    canvas.add(&fgGraphsView);
    canvas.add(&rStatusBackground);
    canvas.add(&rMousePosition);
    canvas.add(&rZoom);
    canvas.add(&svFunctions);
    canvas.add(&vlToolbarButtons);
    
    // Initialize the grapher view
    fgGraphsView.setView(viewStartX, viewEndX, viewStartY);
    
// SANDBOX START
    
// TODO: Make updating zoom text some function bc it is done in three places!
    
    // Add 10 function entries at start by emulating add button press
    for(int i = 0; i < 10; i++)
        bAddEntry.getListener()(&bAddEntry, &canvas);
    
    // Let grapher draw some function
    sgf::FunctionProperties fp(L"f(x)=2x*5");
    fgGraphsView.add(&fp);
    
// SANDBOX END
    
    while(canvas.isActive() && canvas.tick())
    {
        
    }
    
    return 0;
}


