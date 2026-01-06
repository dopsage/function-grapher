
/********** SIMPLE GUI FRAMEWORK FUNCTION GRAPHER MODULE **********/

#ifndef _FUNCTIONGRAPHER_HPP
#define _FUNCTIONGRAPHER_HPP

#include <cmath>
#include <stdexcept>
#include <vector>
#include "SGF/Context.hpp"
#include "SGF/FunctionProperties.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

class FunctionGrapher final : public Rectangle
{
private:
    void                                cacheDefinition(FunctionProperties* function);
    std::vector<FunctionProperties*>    functionPtrs;
    bool                                isViewSet;
    static void                         onFunctionGrapherContextUse(Context* contextPtr, Rectangle* instancePtr, Canvas* canvasPtr);
    static const int                    PIXELS_PER_STEP;
    float                               step;
    ViewProperties                      view;

public:
    FunctionGrapher();
    void            add(FunctionProperties* function);
    void            copy(Rectangle* other)                  override;
    ViewProperties* getViewPtr();
    void            remove(FunctionProperties* function);
    Vector2D        toCanvasPlane(Vector2D grapherCoord)    const;
    Vector2D        toGrapherPlane(Vector2D canvasCoord)    const;
    void            setView(float hS, float hE, float vS);  // horizontal start & end, vertical start
};

}

#endif
