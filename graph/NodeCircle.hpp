#pragma once
#include "VisualObject.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include "EdgeShape.hpp"

class NodeCircle : public VisualObject
{
private:
	sf::CircleShape circle;
	sf::Color outlineColor;
	sf::Text indexText;
	const size_t index;
	bool isSelected{ false };
	std::vector<std::weak_ptr<EdgeShape>> edges;

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

	void Draw(sf::RenderTarget& window) const override;
	void FillWithDefinedColor(DefinedColor color) override;
	bool Intersects(sf::FloatRect rect);
	bool Select(sf::Vector2i& mousePos) override;
	void SetAsNotSelected();
	void SetPosition(sf::Vector2i position);
	void insertEdge(std::weak_ptr<EdgeShape> edge);
	std::vector<std::shared_ptr<EdgeShape>> GetLinkedEdges();
	const size_t GetIndex() const;
	const sf::Vector2i GetPosition() const override;
	const bool GetIsSelected() const;
};
