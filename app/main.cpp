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
    std::vector<size_t> selectedNodeIndex;
    std::vector<NodeCircle> nodesCircle; 
    std::vector<EdgeShape> edgesShape;
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
                std::cout << "soltou\n";
                holding = false;
                if (editMode)
                {
                    std::cout << "setou o edit mode como falso\n";
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
                    std::cout << "entrou no evento de clique\n";
                    for (auto& n : nodesCircle)
                    {
                        if (n.SelectNode(sf::Mouse::getPosition(window)))
                        {
                            std::cout << "selecionou\n";
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
                        std::cout << "ta solto mesmo hein " << selectedNodeIndex.size() << "\n";
                        if (selectedNodeIndex.size() >= 2)
                        {
                            addEdge(
                               nodesCircle.at(selectedNodeIndex.at(0)).getPosition(),
                                nodesCircle.at(selectedNodeIndex.at(1)).getPosition(), 
                                edgesShape);
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
                /*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    editMode = !editMode;
                }*/
            }
        }
        if (holding && selectedNodeIndex.size() == 1 && timeHolding.getElapsedTime().asSeconds() > 1.f)
        {
            editMode = true;
            std::cout << "puxando\n";
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