#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <memory>
#include "EdgeShape.hpp"

class NodeCircle
{
private:
	sf::Vector2i position;
	sf::CircleShape circle;
	sf::Text indexText;
	const size_t index;
	bool isSelected{ false };
	std::vector<std::pair<std::weak_ptr<EdgeShape>, bool>> edges;

public:
	static size_t count;
	NodeCircle(sf::Vector2i position);
	~NodeCircle() = default;

	NodeCircle& operator=(const NodeCircle& other)
	{
		this->position = other.position;
		this->circle = other.circle;
		this->indexText = other.indexText;
		this->isSelected = other.isSelected;
		this->edges = other.edges;
		return *this;
	}

	void Draw(sf::RenderWindow& window) const;
	
	bool Intersects(sf::FloatRect rect);
	bool SelectNode(sf::Vector2i&& mousePos);
	void SetAsNotSelected();
	void setPosition(sf::Vector2i position);
	void insertEdge(std::weak_ptr<EdgeShape> edge, bool isPrimary);
	std::vector<std::shared_ptr<EdgeShape>> GetLinkedEdges()
	{
		std::vector<std::shared_ptr<EdgeShape>> temp;
		for (auto& e : edges)
		{
			if (!e.first.expired())
			{
				temp.push_back(e.first.lock());
			}
		}
		return temp;
	}
	void ChangeColor(sf::Color c)
	{
		circle.setFillColor(c);
	}
	const size_t GetIndex() const;
	const sf::Vector2i getPosition() const;
	const bool getIsSelected() const;
};
