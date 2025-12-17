
#include <iostream>
#include "SGF/Button.hpp"
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Slider.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/Types.hpp"

static const sgf::Color3D   LIST_SLIDER_COLOR({ 0, 255, 0 });
static const float          LIST_SLIDER_WIDTH(20);
static const float          LIST_SLIDER_HANDLE_HEIGHT(100);
    
static const sgf::Color3D   LIST_AREA_COLOR({ 255, 255, 0 });
static const float          LIST_AREA_WIDTH(150);

void onListSliderEvent(float value, int id, sgf::Canvas* canvas);

int main()
{
    /********** CONFIGURE INSTANCES **********/
    
    sgf::Canvas     canvas;
    sgf::Slider     listSlider;
    sgf::Rectangle  listArea;
    
    canvas.setPosition({ 0, 0 });
    canvas.setSize({ 600, 400 });
    canvas.setTickDuration({ 1000/60 });
    canvas.setTitle("Funciton grapher");
    
    listSlider.setColor(LIST_SLIDER_COLOR);
    listSlider.setPosition({ 0, 0 });
    listSlider.setPriority(0);
    listSlider.setSize({ LIST_SLIDER_WIDTH, canvas.getHeight() });
    listSlider.setSliderListener(onListSliderEvent);
    listSlider.setHandleHeight(LIST_SLIDER_HANDLE_HEIGHT);
    listSlider.setMeta(&listArea);
    
    listArea.setColor(LIST_AREA_COLOR);
    listArea.setPosition({ LIST_SLIDER_WIDTH, 0 });
    listArea.setPriority(0);
    listArea.setSize({ LIST_AREA_WIDTH, canvas.getHeight() });
    
    /********** RUN THE FUNCTION GRAPHER APPLICATION **********/

    canvas.add(listSlider);
    canvas.add(listSlider.getHandle());
    
    while(canvas.alive())
    {
        if(canvas.tick())
        {
            // Do updates ...
        }
    }
    
    return 0;
}

void onListSliderEvent(float value, int id, sgf::Canvas* canvas)
{
    sgf::Slider*    listSlider  = (sgf::Slider*)canvas->getRectangle(id);
    sgf::Rectangle* listArea    = (sgf::Rectangle*)listSlider->getMeta();

    if(listArea->getPriority() == 0)
    {
        canvas->add(*listArea);
        listArea->setPriority(1);
    }
}
