
#include <iostream>
#include "SGF/Button.hpp"
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Slider.hpp"
#include "SGF/Types.hpp"

void onKeyboardEvent(sgf::Unicode data, int id, sgf::Canvas* canvas)
{
	std::cout << data << std::endl;
}

void onMouseEvent(sgf::MouseEvent event, sgf::Vector2D position, int id, sgf::Canvas* canvas)
{
    std::cout << (int)event << std::endl;
}

void onSliderEvent(float value, int id, sgf::Canvas* canvas)
{
    std::cout << value << std::endl;
}

void onButtonEvent(int id, sgf::Canvas* canvas)
{
    std::cout << "Click " << *(int*)canvas->getRectangle(id)->getMeta() << std::endl;
}

int main()
{
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
                
    sgf::Button button;
                button
                .setColor({ 255, 0, 0 })
                .setPosition({ 100.F, 100.F })
                .setPriority(2)
                .setSize({ 50.F, 50.F });
                
    // USE METADATA FOR CUSTOM VARIABLES BOND TO INSTANCES OF RECTANGLE
    int x = 2137;
    button.setMeta(&x);
    
    /********** RUN THE FUNCTION GRAPHER APPLICATION **********/
    
    // Debugging purposes
    canvas.getInputParser().setKeyboardReceiver(&mainBackground);
    mainBackground.setKeyboardListener(onKeyboardEvent).setMouseListener(onMouseEvent);
    slider.setSliderListener(onSliderEvent);
    button.setButtonListener(onButtonEvent);

    canvas.add(mainBackground);
    canvas.add(slider);
    canvas.add(slider.getHandle());
    canvas.add(button);
    
    while(canvas.alive())
    {
        if(canvas.tick())
        {
            // Do updates ...
        }
    }
    
    return 0;
}
