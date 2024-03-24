#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "NodeCircle.hpp"
#include "EdgeShape.hpp"

class InputManager
{
private:
    std::vector<size_t> selectedNodeIndex;
    sf::RenderWindow& window;
    std::vector<NodeCircle>& nodes;
    std::list<EdgeShape>& edges;
    sf::Clock timeHolding;
    bool holding{ false };
    bool editMode{ false };

    void AddNodeOnPosition(sf::Vector2i&& position);
    void AddEdge(sf::Vector2i beginingPosition, sf::Vector2i endPosition, std::list<EdgeShape>& edges);

public:
	InputManager(sf::RenderWindow& window, std::vector<NodeCircle>& nodes, std::list<EdgeShape>& edges) ;
	~InputManager() = default;

    void MouseButtonRelease();
    void MouseButtonInput();
    void KeyboardInput();
    void Update();
};
