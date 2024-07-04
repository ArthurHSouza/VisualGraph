#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <optional>
#include "EdgeShape.hpp"
#include "SelectableVisualObject.hpp"
#include "VisualText.hpp"

//The Node visual representation 
class NodeCircle : public SelectableVisualObject
{
private:
	sf::CircleShape circle;
	sf::Color outlineColor;
	VisualText indexText;
	std::optional<VisualText> extraText;
	size_t index;
	bool isSelected{ false };
	std::vector<std::weak_ptr<EdgeShape>> edges;

	static size_t count;
public:
	NodeCircle(sf::Vector2i position);
	~NodeCircle() = default;

	void Draw(sf::RenderTarget& window) const override;
	void FillWithDefinedColor(DefinedColor color) override;
	void FillWithColor(sf::Color c);
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
	NodeCircle& operator=(const NodeCircle& other);
	static void ClearIndexCounter();
	void UpdateIndex();
};
