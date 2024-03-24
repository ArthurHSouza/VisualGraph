#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
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

void addEdge(sf::Vector2i beginingPosition, sf::Vector2i endPosition, std::list<EdgeShape>& edges)
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
    std::vector<size_t> selectedNodeIndex;
    std::vector<NodeCircle> nodesCircle; 
    std::list<EdgeShape> edgesShape;
    sf::Clock timeHolding;
    bool holding = false;
    bool editMode = false;

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
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                holding = false;
                if (editMode)
                {
                    editMode = false;
                    if (!selectedNodeIndex.empty())
                    {
                        nodesCircle.at(selectedNodeIndex.front()).SetAsNotSelected();
                        selectedNodeIndex.clear();
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                //sf::Event::MouseButtonPressed
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    addNodeOnPosition(sf::Mouse::getPosition(window), nodesCircle);
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    selectedNodeIndex.clear();
                    for (auto& n : nodesCircle)
                    {
                        if (n.SelectNode(sf::Mouse::getPosition(window)))
                        {
                           // editMode = !editMode;
                            timeHolding.restart();
                            selectedNodeIndex.push_back(n.GetIndex());
                        }
                    }
                    
                    if (selectedNodeIndex.size() == 1)
                    {
                        holding = true;
                    }

                    if (!holding)
                    {
                        if (selectedNodeIndex.size() >= 2)
                        {
                            addEdge(
                               nodesCircle.at(selectedNodeIndex.front()).getPosition(),
                                nodesCircle.at(selectedNodeIndex.back()).getPosition(),
                                edgesShape
                            );
                            nodesCircle.at(selectedNodeIndex.front()).insertEdge(edgesShape.back(), true);
                            nodesCircle.at(selectedNodeIndex.back()).insertEdge(edgesShape.back(), false);
                            for (auto& v : nodesCircle) v.SetAsNotSelected();
                        }
                        //selectedNodeIndex.clear();
                    }
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
        if (holding && selectedNodeIndex.size() == 1 && timeHolding.getElapsedTime().asSeconds() > 0.6f)
        {
            editMode = true;
            nodesCircle.at(selectedNodeIndex.front()).setPosition(sf::Mouse::getPosition(window));
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