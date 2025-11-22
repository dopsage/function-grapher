
#include <iostream>
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Slider.hpp"
#include "SGF/Types.hpp"

void onKeyboardEvent(sgf::Unicode data, void* payload)
{
	std::cout << data << " | " << *(int*)payload << std::endl;
}

void onMouseEvent(sgf::MouseEvent event, sgf::Vector2D position, void* payload)
{
    std::cout << (int)event << " | " << *(int*)payload << std::endl;
}

void onSliderEvent(float value, void* payload)
{
    std::cout << value << " | " << *(int*)payload << std::endl;
}

int main()
{
    int x = 2137;
    
    /********** CONFIGURE RECTANGLE INSTANCES **********/
    
    sgf::Canvas canvas;
                canvas
                .setDrawingFrequency(60.F)
                .setSize({ 600, 400 })
                .setTitle("Simple GUI Framework");
                
    sgf::Rectangle mainBackground;
                   mainBackground
                   .setColor({ 255, 255, 255 })
				   .setPosition({ 0.F, 0.F })
				   .setPriority(0)
				   .setSize(canvas.getSize());
                   
    sgf::Slider slider;
                slider
                .setColor({ 0, 255, 0 })
                .setPosition({ 0.F, 0.F })
                .setPriority(1)
                .setSize({ 20.F, canvas.getHeight() });

    /********** RUN THE FUNCTION GRAPHER APPLICATION **********/
    
    // Debugging purposes
    canvas.getInputParser().setKeyboardReceiver(&mainBackground);
    mainBackground.setKeyboardListener(onKeyboardEvent, &x).setMouseListener(onMouseEvent, &x);
    slider.setSliderListener(onSliderEvent, &x);

    canvas.add(mainBackground);
    canvas.add(slider);
    canvas.add(slider.getHandle());
    
    while(canvas.alive())
    {
        if(canvas.tick())
        {
            // Do updates ...
        }
    }
    
    return 0;
}
