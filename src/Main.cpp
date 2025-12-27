
#include <iostream>
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/ScrollView.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/Types.hpp"

static void onTextInputEvent(const std::string& content, int id, sgf::Canvas* canvas);

static bool run;

int main()
{
    /********** CONFIGURE INSTANCES **********/
    
    sgf::Canvas     cCanvas;
    sgf::Rectangle  rBackground;
    sgf::ScrollView svExpressions;
    
    cCanvas.setPosition({ 1920/2, 0 });
    cCanvas.setSize({ 600, 400 });
    cCanvas.setTickDuration({ 1000/60 });   // It works, but the loop still wastes CPU power (100% usage)
    cCanvas.setTitle("Function grapher");
    
    rBackground.setColor({ 0, 0, 0 });
    rBackground.setPosition({ 0, 0 });
    rBackground.setPriority(0);
    rBackground.setSize({ cCanvas.getWidth(), cCanvas.getHeight() });
    
    svExpressions.setColor({ 255, 255, 0 });
    svExpressions.setPosition({ 0, 0 });
    svExpressions.setPriority(1);
    svExpressions.setSize({ 150.F, cCanvas.getHeight() });
    svExpressions.setSliderWidth(25.F);
    
    /********** RUN THE FUNCTION GRAPHER APPLICATION **********/
    
    // Fill the scroll view list with text inputs
    const int           TIC = 20;
    sgf::TextProperties tpProps[TIC];
    sgf::TextInput      tiInputs[TIC];
    for(int tid = 0; tid < TIC; tid++)
    {
        tpProps [tid] = { {0, 0, 0}, "", 16 };
        
        tiInputs[tid].setBlinkDuration(100);
        tiInputs[tid].setColor({ 64, 64, 0 });
        tiInputs[tid].setCursorWidth(2);
        tiInputs[tid].setFilter(sgf::InputFilter::MATH);
        tiInputs[tid].setLeftPadding(10);
        tiInputs[tid].setListener(onTextInputEvent);
        tiInputs[tid].setPosition({ 100, 100 });
        tiInputs[tid].setSize({ 192, 36 });
        tiInputs[tid].getField().setText(&tpProps[tid]);
        tiInputs[tid].setVerticalPadding(5);
        svExpressions.getList().insert(tid, tiInputs[tid]);
    }
    
    //debug
    tpProps[0].content = ".#.";
    tpProps[1].content = ".#";
    tpProps[2].content = "#.";
    tpProps[3].content = "###VV^^B %$";
    
    cCanvas.add(rBackground);
    cCanvas.add(svExpressions);
    
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

static void onTextInputEvent(const std::string& content, int id, sgf::Canvas* canvas)
{
    std::cout << "TextInputListener[id=" << id << "]: " << content << std::endl;
}
