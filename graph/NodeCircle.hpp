#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "EdgeShape.hpp"

class NodeCircle
{
private:
	sf::Vector2i position;
	sf::CircleShape circle;
	sf::Text indexText;
	const size_t index;
	bool isSelected{ false };
	std::vector<std::pair<EdgeShape&, bool>> edges;

public:
	static size_t count;
	NodeCircle(sf::Vector2i position);
	~NodeCircle() = default;

	void Draw(sf::RenderWindow& window) const;
	
	bool Intersects(sf::FloatRect rect);
	bool SelectNode(sf::Vector2i&& mousePos);
	void SetAsNotSelected();
	void setPosition(sf::Vector2i position);
	void insertEdge(EdgeShape& edge, bool isPrimary);

	const size_t GetIndex() const;
	const sf::Vector2i getPosition() const;
	const bool getIsSelected() const;
};
