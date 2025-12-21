
#include <iostream>
#include "SGF/Button.hpp"
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/ScrollView.hpp"
#include "SGF/Slider.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/Types.hpp"
#include "SGF/VList.hpp"

static const sgf::Color3D   LIST_SLIDER_COLOR({ 0, 255, 0 });
static const float          LIST_SLIDER_WIDTH(20);
static const float          LIST_SLIDER_HANDLE_HEIGHT(100);
    
static const sgf::Color3D   LIST_AREA_COLOR({ 255, 255, 0 });
static const float          LIST_AREA_WIDTH(150);

static void                 onBackgroundKeyboardEvent(int data, int id, sgf::Canvas* canvas);

static bool                 run;

// DEBUG for VLIST TEST
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time()

int main()
{
    /********** CONFIGURE INSTANCES **********/
    
    sgf::Canvas     canvas;
    sgf::Rectangle  background;
    sgf::ScrollView expView;
    sgf::VList      list;
    
    canvas.setPosition({ 0, 0 });
    canvas.setSize({ 600, 400 });
    canvas.setTickDuration({ 1000/60 });
    canvas.setTitle("Funciton grapher");
    canvas.getInputParser().setKeyboardReceiver(&background);
    
    background.setColor({ 0, 0, 0 });
    background.setKeyboardListener(onBackgroundKeyboardEvent);
    background.setPosition({ 0, 0 });
    background.setPriority(0);
    background.setSize({ canvas.getWidth(), canvas.getHeight() });
    
    expView.setColor({ 255, 255, 0 });
    expView.setPosition({ 0, 0 });
    expView.setPriority(1);
    expView.setSize({ 150, canvas.getHeight() });
    expView.setSliderWidth(25.F);
    
// QUICK VLIST TEST
    
    list.setPosition({ 10, 10 });
    list.setPriority(1);
    
    sgf::Rectangle m1;
    m1.setPosition({ 40, 40 });
    m1.setSize({ 40, 40 });
    m1.setColor({ 255, 0, 0 });
    sgf::Rectangle m2;
    m2.setPosition({ 60, 60 });
    m2.setSize({ 60, 60 });
    m2.setColor({ 0, 255, 0 });
    sgf::Rectangle m3;
    m3.setPosition({ 80, 80 });
    m3.setSize({ 80, 80 });
    m3.setColor({ 0, 0, 255 });
    sgf::Rectangle m4;
    m4.setPosition({ 100, 100 });
    m4.setSize({ 100, 100 });
    m4.setColor({ 255, 255, 255 });
    
    std::srand(std::time(0)); // seed with current time
    list.insertMember(0, m1);
    list.insertMember(std::rand() % 2, m2);
    list.insertMember(std::rand() % 3, m3);
    list.insertMember(std::rand() % 4, m4);
    //list.setVisible(true); // Optional, but not yet implemented!
    
    std::cout << "Size of list: " << list.getWidth() << " " << list.getHeight() << std::endl;
    
    /********** RUN THE FUNCTION GRAPHER APPLICATION **********/

    // Idea: make something like onAdd callbacks for rectangles that are invoked when canvas adds them
    // it could be used to recursively add other rectangles by overriding this callback by rectangle-driven classes like slider
    canvas.add(background);
    //canvas.add(expView);
    //canvas.add(expView.getSlider());
    //canvas.add(expView.getSlider().getHandle());
    //canvas.add(expView.getList());
    //canvas.add(list);
    for(int i = 0; i < list.getMemberCount(); i++)
        canvas.add(*list.getMemberRectangle(i));
    
    run = true;
    while(canvas.alive())
    {
        if(canvas.tick())
        {
            if(!run)
                canvas.kill();
            
            // Do updates ...
        }
    }
    
    return 0;
}

static void onBackgroundKeyboardEvent(int data, int id, sgf::Canvas* canvas)
{
    if(data == -36)
        run = false;
}
