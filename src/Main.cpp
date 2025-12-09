
#include <iostream>
#include "SGF/Button.hpp"
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Slider.hpp"
#include "SGF/TextInput.hpp"
#include "SGF/Types.hpp"

void onSliderEvent(float value, int id, sgf::Canvas* canvas)
{
    std::cout << value << std::endl;
    
    // Update text properties according to the slider value
    sgf::Rectangle* handle = canvas->getRectangle(2);
	handle->getText()->size = (unsigned int)(8 + (int)(value * 16));
	handle->getText()->color.r = (sgf::Byte)(value * 255);
	handle->getText()->color.b = (sgf::Byte)(value * 255);
	handle->updateText();
    
    // Update text input padding values
    sgf::TextInput* input = (sgf::TextInput*)canvas->getRectangle(4);
    input->setLeftPadding(value * 20.F);
    input->setVerticalPadding(value * 20.F);
}

void onButtonEvent(int id, sgf::Canvas* canvas)
{
    sgf::TextInput* input = (sgf::TextInput*)canvas->getRectangle(4);
    const std::string& content = *input->getContent();
    
    std::cout << 
    ((content == "Celisracist") ?
    "It would never happen, stop lying" :
    "Ye, ye, of course") << std::endl;
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
                   
    sgf::TextProperties handleText = { sgf::Color3D({0, 0, 0}), "Alj", 8 };
    sgf::Slider slider;
                slider
                .setColor({ 0, 255, 0 })
                .setPosition({ 0.F, 0.F })
                .setPriority(1)
                .setSize({ 20.F, canvas.getHeight() });
    slider.getHandle().setText(&handleText);
    slider.setSliderListener(onSliderEvent);
                
    sgf::Button button;
                button
                .setColor({ 255, 0, 0 })
                .setPosition({ 100.F, 100.F })
                .setPriority(2)
                .setSize({ 50.F, 50.F });
    button.setButtonListener(onButtonEvent);
    
    sgf::TextProperties inputText = { sgf::Color3D({ 0, 0, 0 }), "", 16 };
    sgf::TextInput input;
                   input
                   .setLeftPadding(20.F)
                   .setVerticalPadding(20.F)
                   .setColor({ 0, 0, 255 })
                   .setPosition({ 100.F, 200.F })
                   .setPriority(3)
                   .setSize({ 250.F, 80.F });
    input.getField().setText(&inputText);
    
    /********** RUN THE FUNCTION GRAPHER APPLICATION **********/

    canvas.add(mainBackground);
    canvas.add(slider);
    canvas.add(slider.getHandle());
    canvas.add(button);
    canvas.add(input);
    canvas.add(input.getField());
    
    while(canvas.alive())
    {
        if(canvas.tick())
        {
            // Do updates ...
        }
    }
    
    return 0;
}
