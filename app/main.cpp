#include <SFML/Graphics.hpp>
#include <vector>
#include "NodeCircle.hpp"

void addNodeOnScreen(sf::RenderWindow& window, std::vector<NodeCircle>& nodes)
{
    nodes.emplace_back(sf::Mouse::getPosition(window));
}

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    std::vector<NodeCircle> nodesCircle; 
    nodesCircle.reserve(10);
    //nodesCircle.emplace_back(sf::Vector2f(100, 100));

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    addNodeOnScreen(window, nodesCircle);
                }
            }
        }

        window.clear(sf::Color::Yellow);
        
        for (auto& node : nodesCircle)
        {
            node.DrawShape(window);
        }

        window.display();
    }
}