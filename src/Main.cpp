
#include <iostream>
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/ScrollView.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/Types.hpp"

static bool run;

int main()
{
    /********** CONFIGURE INSTANCES **********/
    
    sgf::Canvas     cCanvas;
    sgf::Rectangle  rBackground;
    sgf::ScrollView svExpressions;
    
    cCanvas.setPosition({ 0, 0 });
    cCanvas.setSize({ 600, 400 });
    cCanvas.setTickDuration({ 1000/60 });
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
        tpProps [tid] = { {0, 0, 0}, "", 16 };  // This segfaults when content is not an empty string!
        tiInputs[tid].setBlinkDuration(100);
        tiInputs[tid].setColor({ 64, 64, 0 });
        tiInputs[tid].setCursorWidth(2);
        tiInputs[tid].setLeftPadding(10);
        tiInputs[tid].setPosition({ 100, 100 });
        tiInputs[tid].setSize({ 200, 80 });
        tiInputs[tid].getField().setText(&tpProps[tid]);
        tiInputs[tid].setVerticalPadding(10);
        svExpressions.getList().insert(tid, tiInputs[tid]);
    }
    
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
