#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <optional>
#include "EdgeShape.hpp"
#include "SelectableVisualObject.hpp"
#include "VisualText.hpp"

class NodeCircle : public SelectableVisualObject
{
private:
	sf::CircleShape circle;
	sf::Color outlineColor;
	VisualText indexText;
	std::optional<VisualText> extraText;
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
	void FillOutlineWithDefinedColor(DefinedColor color);
	bool Intersects(sf::FloatRect rect);
	bool Select(sf::Vector2i& mousePos) override;
	void SetAsNotSelected();
	void SetPosition(sf::Vector2i position);
	void InsertEdge(std::weak_ptr<EdgeShape> edge);
	void AddText(std::string text);
	std::vector<std::shared_ptr<EdgeShape>> GetLinkedEdges();
	const size_t GetIndex() const;
	const sf::Vector2i GetPosition() const override;
	const bool GetIsSelected() const;
};
