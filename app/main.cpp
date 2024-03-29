#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <memory>
#include "NodeCircle.hpp"
#include "EdgeShape.hpp"
#include "InputManager.hpp"
#include <iostream>

int main()
{
    std::vector<NodeCircle> nodesCircle; 
    std::list<std::shared_ptr<EdgeShape>> edgesShape;

    auto window = sf::RenderWindow{ { 1920u, 1080u}, "CMake SFML Project"};
    window.setFramerateLimit(144);
    sf::View cam;
    sf::Vector2i previusMousePosition;
    auto windowSize = sf::Vector2f(window.getSize());
    cam.setSize(windowSize);
    cam.setCenter(windowSize / 2.f);
    bool isDragging{ false };
    const float maxZoomIn{ 0.8f };
    const float maxZoomOut{ 2.f };
    const sf::Vector2f originalViewSize = cam.getSize();

    InputManager inputManager(window, nodesCircle, edgesShape);

    while (window.isOpen())
    {
        window.setView(cam);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            cam.move(1, 0);
        }
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
            else if (event.type == sf::Event::Resized)
            {
                cam.setSize(event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta < 0 && (cam.getSize().x / originalViewSize.x) < maxZoomOut)
                {
                    cam.zoom(1.1f);
                }
                else  if (event.mouseWheelScroll.delta > 0 && (cam.getSize().x / originalViewSize.x) > maxZoomIn)
                {
                    cam.zoom(0.9f);
                }
            
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                isDragging = false;
                inputManager.MouseButtonRelease();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
                {
                    isDragging = true;
                }
                inputManager.MouseButtonInput();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                inputManager.KeyboardInput();
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (isDragging) {
                    const sf::Vector2f delta = window.mapPixelToCoords(mousePosition) - window.mapPixelToCoords(previusMousePosition);
                    cam.move(-delta);
                }
                previusMousePosition = mousePosition;
            }
        }
        
        inputManager.Update();

        window.clear(sf::Color::White);
        
        for (auto& e : edgesShape)
        {
            e->Draw(window);
        }
        for (auto& node : nodesCircle)
        {
            node.Draw(window);
        }

        window.display();
    }
}