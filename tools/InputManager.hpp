#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <memory>
#include <forward_list>
#include <algorithm>
#include "NodeCircle.hpp"
#include "EdgeShape.hpp"
#include "Camera.hpp"

class InputManager
{
private:
	std::vector<size_t> selectedNodeIndex;
	sf::RenderWindow& window;
	std::vector<NodeCircle>& nodes;
	std::forward_list<std::shared_ptr<EdgeShape>>& edges;
	Camera& cam;
	std::optional<sf::Clock> timeHolding;

	bool holding{ false };
	bool editMode{ false };
	bool deleteMode{ false };
	bool isDragging{ false };
	const float timeToEdit{ 0.2f };
	sf::Vector2i mousePosition;
	sf::Vector2i previousMousePosition;

	void AddNodeOnPosition(sf::Vector2i& position);
	void DeleteNode(size_t index);
	void AddEdge(NodeCircle& begining, NodeCircle end);
	void DeleteEdge();

	void MouseButtonRelease();
	void MouseButtonInput();
	void KeyboardInput();

public:
	InputManager(sf::RenderWindow& window, Camera& cam, std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges);
	~InputManager() = default;

	void Update();
};
