
#include <iostream>
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Slider.hpp"
#include "SGF/Types.hpp"

void onKeyboardEvent(sgf::Unicode data, void* payload)
{
	std::cout << data << " | " << *(int*)payload << std::endl;
}

int main()
{
    int x = 2137;
    sgf::Canvas    canvas;
    sgf::Rectangle mainBackground;
    sgf::Slider    slider;
    sgf::Slider    S2;
    
    canvas.setDrawingFrequency(60.F)
          .setSize({ 600, 400 })
          .setTitle("Simple GUI Framework")
          .getInputParser().setKeyboardReceiver(&mainBackground);
    mainBackground.setColor({ 255, 0, 0 })
				  .setPosition({ 0.F, 0.F })
				  .setPriority(0)
				  .setSize(canvas.getSize()).setKeyboardListener(onKeyboardEvent, &x);
    slider.setColor({ 0, 255, 0 })
		  .setPosition({ 100.F, 100.F })
		  .setPriority(1)
		  .setSize({ 50.F, canvas.getHeight() / 2 });
	S2.setColor({ 0, 0, 255 })
		  .setPosition({ 130.F, 120.F })
		  .setPriority(2)
		  .setSize({ 50.F, canvas.getHeight() / 2 });

    // Configure instances
    
    canvas.add(mainBackground);
    canvas.add(slider);
    canvas.add(S2);
    canvas.add(slider.getHandle());  // make it more comfy in futurrrrrrr...
	canvas.add(S2.getHandle());
    
    while(canvas.alive())
    {
        if(canvas.tick())
        {
            // Do updates ...
        }
    }
    
    return 0;
}
