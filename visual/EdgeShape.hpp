#pragma once
#include "SelectableVisualObject.hpp"

class EdgeShape : public SelectableVisualObject
{
private:
	const std::size_t begningIndex;
	const std::size_t endIndex;
	sf::RectangleShape arrowRect;
	sf::ConvexShape arrowHead;
	sf::Vector2i endPosition;
	sf::RectangleShape collisionPoint;
	bool drawCollisionPoint{ false };

	void UpdateArrowHead(const int& difX,const float& distance);

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

	bool Select(sf::Vector2i& mousePos) override;

};
