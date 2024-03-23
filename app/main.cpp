#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <ranges>
#include "NodeCircle.hpp"
#include "EdgeShape.hpp"
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

void addEdge(sf::Vector2i beginingPosition, sf::Vector2i endPosition, std::vector<EdgeShape>& edges)
{
    for (auto& e : edges)
    {
        if (e.getBeginingPosition() == beginingPosition && e.getEndPosition() == endPosition)
        {
            return;
        }
    }
    edges.emplace_back(beginingPosition, endPosition);
}

int main()
{
    std::vector<NodeCircle> selectedNodes;
    std::vector<NodeCircle> nodesCircle; 
    std::vector<EdgeShape> edgesShape;

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

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
                        n.SelectNode(sf::Mouse::getPosition(window));
                    }
                   
                    std::copy_if(nodesCircle.begin(), nodesCircle.end(), std::back_inserter(selectedNodes),
                        [](NodeCircle& n)
                        {
                            return n.getIsSelected();
                        }
                        );
                    if (selectedNodes.size() == 2)
                    {
                        addEdge(selectedNodes.at(0).getPosition(), selectedNodes.at(1).getPosition(), edgesShape);
                        for (auto& v : nodesCircle) v.SetAsNotSelected();
                    }
                    selectedNodes.clear();
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                {
                    NodeCircle::count = 0;
                    nodesCircle.clear();
                    edgesShape.clear();

                }
            }
        }
 
        window.clear(sf::Color::Yellow);
        
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