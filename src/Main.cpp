
/*** CODE OF ALL SOURCES IS MESSY BUT THIS IS INTENDED, NOW IT NEEDS REFACTORING PHASE QUICK
 *** BEFORE I FORGOT THE COMPLEXITY THOUGH. ***/

#include <iostream>
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Slider.hpp"
#include "SGF/Types.hpp"

// TODO: Write docs to hpp and cpps because it is gettin big!
// Whole lib works like a SFML wrapper, not deriver.

// Canvas controls how inputmanager perceives, input manager invokes appropriate callbacks of given rectangle tuple, those rects define list of
// listeners that are appropriatelly activated by IM. code is not pretty bc it was made to work, refactor should be done to not lose yourself here.!.!.!

static sgf::Rectangle mainBackground;
static sgf::Slider    slider;
static sgf::Slider 	  S2;
static sgf::Canvas    canvas;

void onStart();
void onPaint();
void onFinish();

void onKeyboardEvent(sgf::Unicode data, void* payload)
{
	std::cout << data << " | " << *(int*)payload << std::endl;
}

int main()
{
    onStart();
    
    while(canvas.alive())
        if(canvas.tick())
            onPaint();
            
    onFinish();
    return 0;
}

// must be staticly scoped, otherwise referencing it as payload is dangerous!
// it happens because stack is scoped on main, but events happen afterwards thus x
// becomes unknown just after main ends...
static int x = 2137;

void onStart()
{
    // Initialize variables
    
    canvas.setDrawingFrequency(60.F)
          .setSize({ 600, 400 })
          .setTitle("Simple GUI Framework").getInputManager().setKeyboardReceiver(&mainBackground);
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
}

void onPaint()
{
	//std::cout << "Debug: " << slider.getHandle().getPriority() << std::endl;
}

void onFinish()
{
	
}
