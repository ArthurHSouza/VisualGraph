#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <array>
#include <string>
#include "NodeCircle.hpp"
#include "EdgeShape.hpp"
#include "InputManager.hpp"
#include <iostream>

int main()
{
    std::vector<NodeCircle> nodesCircle; 
    std::list<EdgeShape> edgesShape;

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    InputManager inputManager(window, nodesCircle, edgesShape);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                inputManager.MouseButtonRelease();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                inputManager.MouseButtonInput();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                inputManager.KeyboardInput();
            }
        }
        
        inputManager.Update();

        window.clear(sf::Color::White);
        
        for (auto& e : edgesShape)
        {
            e.Draw(window);
        }
        for (auto& node : nodesCircle)
        {
            node.Draw(window);
        }

        window.display();
    }
}