#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <list>
#include "NodeCircle.hpp"
#include "EdgeShape.hpp"

class InputManager
{
private:
    std::vector<size_t> selectedNodeIndex;
    sf::RenderWindow& window;
    std::vector<NodeCircle>& nodes;
    std::list<std::shared_ptr<EdgeShape>>& edges;
    sf::Clock timeHolding;
    bool holding{ false };
    bool editMode{ false };
    bool deleteMode{ false };
    const float timeToEdit{ 0.2f };

    void AddNodeOnPosition(sf::Vector2i&& position);
    void DeleteNode(size_t index);
    void AddEdge(sf::Vector2i beginingPosition, sf::Vector2i endPosition);

public:
	InputManager(sf::RenderWindow& window, std::vector<NodeCircle>& nodes, std::list<std::shared_ptr<EdgeShape>>& edges) ;
	~InputManager() = default;

    void MouseButtonRelease();
    void MouseButtonInput();
    void KeyboardInput();
    void Update();
};
