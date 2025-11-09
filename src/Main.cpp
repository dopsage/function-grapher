
#include <iostream>
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"
#include "SGF/Types.hpp"

// TODO: Write docs to hpp and cpps because it is gettin big!
// Whole lib works like a SFML wrapper, not deriver.

// Canvas controls how inputmanager perceives, input manager invokes appropriate callbacks of given rectangle tuple, those rects define list of
// listeners that are appropriatelly activated by IM. code is not pretty bc it was made to work, refactor should be done to not lose yourself here.!.!.!

static sgf::Rectangle background;
static sgf::Rectangle button;
static sgf::Canvas    canvas;

void onStart();
void onPaint();
void onFinish();

void onButtonKeyboardCallback(sgf::Unicode data);
void onButtonMouseCallback(bool isDown, sgf::Vector2D position);

int main()
{
    onStart();
    
    while(canvas.alive())
        if(canvas.tick())
            onPaint();
            
    onFinish();
    return 0;
}

void onStart()
{
    // Initialize variables
    
    canvas.setDrawingFrequency(30.F)
          .setSize({ 600, 400 })
          .setTitle("Simple GUI Framework")
          .getInputManager().setKeyboardReceiver(&button);
          
    background.setColor({ 255, 0, 0 })
              .setPosition({0.F, 0.F})
              .setPriority(0)
              .setSize(canvas.getSize());
              
    button.setColor({ 0, 255, 0 })
          .setKeyboardListener(onButtonKeyboardCallback)
          .setMouseListener(onButtonMouseCallback)
          .setPosition({ 50.F, 50.F })
          .setPriority(1)
          .setSize({ 150.F, 75.F });

    // Configure instances
    
    canvas.add(background);
    canvas.add(button);
    
    std::cout << "Canvas is alive" << std::endl;
}

void onPaint()
{
    
}

void onFinish()
{
    std::cout << "Canvas got killed" << std::endl;
}

void onButtonKeyboardCallback(sgf::Unicode data)
{
    std::cout << "Keyboard: " << data << ", time=" << canvas.getElapsedTime() << std::endl;
}

void onButtonMouseCallback(bool isDown, sgf::Vector2D position)
{
    std::cout << "Mouse: " << isDown << " | " << position.x << "," << position.y <<
    ", time=" << canvas.getElapsedTime() << std::endl;
}
