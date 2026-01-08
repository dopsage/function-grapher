
//#include <iostream>
#include "SGF/FunctionGrapher.hpp"

using namespace sgf;

void FunctionGrapher::cacheDefinition(FunctionProperties* function)
{
    // Somehow interpret function definition
    // ...
    
    // Fill mapping cache
    function->mappingCache.clear();
    int     sC  = this->getWidth() / PIXELS_PER_STEP;   // [-]      step count
    float   sL  = (view.hE - view.hS) / sC;             // [units]  step length
    for(int sI = 0; sI <= sC; sI++)
    {
        float fA = view.hS + sI * sL;   // Function argument
        float fV = fA * std::sin(fA);   // Function value (for now it is always f(x)=x*sin(x))
        function->mappingCache[fA] = fV;
    }
}

void FunctionGrapher::onFunctionGrapherContextUse(Context* contextPtr, Rectangle* instancePtr, Canvas* canvasPtr)
{
    FunctionGrapher* fg = (FunctionGrapher*)instancePtr;
    
    if(!fg->isViewSet) return;

    /*** Draw graphing plane unit ticks for both axes ***/
    
    for(int hgC = fg->view.hsT; hgC <= fg->view.heT; hgC++)
    {
        float hcC = fg->toCanvasPlane({ (float)hgC, 0.0f }).x;
        contextPtr->line(
            { hcC, fg->getY() },
            { hcC, fg->getY() + fg->getHeight() },
            { sgf::Byte(!hgC ? 255 : 0), 0, 0 },
            2
        );
    }
    for(int vgC = fg->view.vsT; vgC <= fg->view.veT; vgC++)
    {
        float vcC = fg->toCanvasPlane({ 0.0f, (float)vgC }).y;
        contextPtr->line(
            { fg->getX(), vcC },
            { fg->getX() + fg->getWidth(), vcC },
            { sgf::Byte(!vgC ? 255 : 0), 0, 0 },
            2
        );
    }
    
    /*** Draw registered function graphs using their mapping cache ***/
    
    for(FunctionProperties* function : fg->functionPtrs)
    {
        // Refresh mapping cache of the registered function if it has the refresh flag set
        if(function->refreshFlag)
        {
            fg->cacheDefinition(function);
            function->refreshFlag = false;
        }
        
        /* With ensured freshness of mapping cache, draw the graph by drawing lines
         * that approximate the perfect graph curve. Remember about coorinate plane
         * transformations! */
        auto left   = function->mappingCache.begin();
        auto right  = function->mappingCache.begin();
        for(++right; right != function->mappingCache.end(); left++, right++)
        {
            contextPtr->line(
                { fg->toCanvasPlane({ left->first,  left->second  }) },
                { fg->toCanvasPlane({ right->first, right->second }) },
                { 0, 0, 255 },
                2
            );
        }
    }
    
    // Debug lines
    //contextPtr->line({fg->getX(), fg->getY()+fg->getHeight()/2},{fg->getX()+fg->getWidth(), fg->getY()+fg->getHeight()/2}, {0,255,0}, 2);
    //contextPtr->line({fg->getX()+fg->getWidth()/2, fg->getY()},{fg->getX()+fg->getWidth()/2, fg->getY()+fg->getHeight()}, {0,255,0}, 2);
}

const int FunctionGrapher::PIXELS_PER_STEP = 8;

FunctionGrapher::   FunctionGrapher() :
                    Rectangle::Rectangle(),
                    functionPtrs(),
                    isViewSet(false),
                    step(0.0f)
{
    setContextListener(FunctionGrapher::onFunctionGrapherContextUse);
}

void FunctionGrapher::add(FunctionProperties* function)
{
    if(std::find(functionPtrs.begin(), functionPtrs.end(), function) == functionPtrs.end())
    {
        // Trigger immediate update before registration
        function->refreshFlag = true;
        functionPtrs.push_back(function);
    }
}

void FunctionGrapher::copy(Rectangle* other)
{
    // Not implemented yet, there was no need ...
    throw std::logic_error("FunctionGraph::copy is not implemented");
}

ViewProperties* FunctionGrapher::getViewPtr()
{
    return &view;
}

void FunctionGrapher::remove(FunctionProperties* function)
{
    std::vector<FunctionProperties*>::iterator it =
    std::find(functionPtrs.begin(), functionPtrs.end(), function);
    
    if(it != functionPtrs.end())
        functionPtrs.erase(it);
}

Vector2D FunctionGrapher::toCanvasPlane(Vector2D grapherCoord) const
{
    return
    {
        // Actually i got this by solving for canvasCoord from the equations in toGrapherPlane
        (grapherCoord.x - view.hS) * view.pixelsPerUnit + this->getX(),
        this->getY() - (grapherCoord.y - view.vE) * view.pixelsPerUnit
    };
}

Vector2D FunctionGrapher::toGrapherPlane(Vector2D canvasCoord) const
{
    return
    {
        // Simple math, remember about screen coordinate space (Y grows downwards!)
        view.hS + (canvasCoord.x - this->getX()) / view.pixelsPerUnit,
        view.vE - (canvasCoord.y - this->getY()) / view.pixelsPerUnit
    };
}

void FunctionGrapher::setView(float hS, float hE, float vS)
{
    if(this->getWidth() < 1 || this->getHeight() < 1 || hE <= hS) return;

    view.pixelsPerUnit  = this->getWidth() / (hE - hS);

    // Initialize horizontal axis
    view.hE    = hE;
    view.hS    = hS;
    view.heT   = std::floor(hE);
    view.hsT   = std::ceil(hS);
    
    // Initialize vertical axis
    view.vE    = vS + this->getHeight() / view.pixelsPerUnit;
    view.vS    = vS;
    view.veT   = std::floor(view.vE);
    view.vsT   = std::ceil(vS);
    
    isViewSet = true;
    
    // Schedule all registered functions for refreshal so they fit the new view
    for(FunctionProperties* function : functionPtrs)
        function->refreshFlag = true;
}
