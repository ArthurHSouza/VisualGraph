#pragma once
#include "SelectableVisualObject.hpp"
#include "VisualText.hpp"
#include <iostream>
class EdgeShape : public SelectableVisualObject
{
private:
	const std::size_t begningIndex;
	const std::size_t endIndex;
	const float weight = 4.25f;
	VisualText weightText;
	sf::RectangleShape arrowRect;
	sf::ConvexShape arrowHead;
	sf::Vector2i endPosition;
	sf::RectangleShape collisionPoint;
	bool drawCollisionPoint{ false };
	void UpdateArrowHead(const int& diffY,const float& distance);
	void UpdateWeightText();

public:
	EdgeShape(std::size_t begningIndex,std::size_t endIndex, sf::Vector2i begining, sf::Vector2i end);
	~EdgeShape() = default;

	void Draw(sf::RenderTarget& window) const override;
	void Update(sf::Vector2i begining, sf::Vector2i end, bool shallChangePosition = false);
	void FillWithDefinedColor(DefinedColor color) override;
	
	const sf::Vector2i GetPosition() const override;
	const sf::Vector2i GetEndPosition() const;

	const std::size_t GetBeginingIndex() const;
	const std::size_t GetEndIndex() const;
	const float GetWeight() const;
	bool Select(sf::Vector2i& mousePos) override;
};
