#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "NodeCircle.hpp"
#include <iostream>

void addNodeOnPosition(sf::Vector2i&& position, std::vector<NodeCircle>& nodes)
{
    sf::Rect<float> tempRect(sf::Vector2f(position), sf::Vector2f(2, 2));
    for (auto& i : nodes)
    {
        if(i.Intersects(tempRect))
            return;
    }
    nodes.emplace_back(position);
}

int main()
{
    std::array<int, 2> selectedIndex{ -1, -1 };
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
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    addNodeOnPosition(sf::Mouse::getPosition(window), nodesCircle);
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    for (auto& n : nodesCircle)
                    {
                        int temp = n.SelectNode(sf::Mouse::getPosition(window));
                        if (temp != -1)
                        {
                            if (selectedIndex[0] == -1)
                            {
                                selectedIndex[0] = temp;
                            }
                            else
                            {
                                selectedIndex[1] = temp;
                            }
                            break;
                        }
                    }
                    if (selectedIndex[0] != -1 && selectedIndex[1] != -1)
                    {
                        for (int i{}; i < 2; i++)
                        {
                            nodesCircle[selectedIndex[i]].SetAsNotSelected();
                            selectedIndex[i] = -1;
                        }
                    }
                    std::cout << "valor do primeiro i " << selectedIndex[0] << " segundo " << selectedIndex[1] << "\n";
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