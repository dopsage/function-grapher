
#include <iostream>
#include "SGF/Canvas.hpp"
#include "SGF/Rectangle.hpp"

// TODO: Write docs to hpp and cpps because it is gettin big!

// Whole lib works like a SFML wrapper, not deriver.

int main()
{
    // Prepare things.
    sgf::Canvas canvas(600, 400, "Simple GUI Framework", 30.F);
    auto background = sgf::Rectangle({20.F, 20.F}, {560.F, 360.F}, 0).setColor({ 255, 0, 0 });
    auto button     = sgf::Rectangle().setPosition({ 50.F, 50.F }).setSize({ 150.F, 75.F }).setPriority(1).setColor({ 0, 255, 0 });
    canvas.add(background);
    canvas.add(button);

    // Run the canvas application.
    while(canvas.alive())
    {
        if(!canvas.draw()) continue;

        // Debugs
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(canvas.getSfmlWindow());
            button.setPosition({(float)pos.x, (float)pos.y});
        }
    }

    // Canvas exit notification.
    sgf::Error error = canvas.getError();
    std::cout << "Canvas exited with error code " << (int)error << std::endl;
    return error;
}
