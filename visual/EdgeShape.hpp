#pragma once
#include "SelectableVisualObject.hpp"

class EdgeShape : public SelectableVisualObject
{
private:
	const int begningIndex;
	const int endIndex;
	sf::RectangleShape arrowRect;
	sf::Vector2i endPosition;
	sf::RectangleShape collisionPoint;
	bool drawCollisionPoint{ false };

public:
	EdgeShape(int begningIndex,int endIndex, sf::Vector2i begining, sf::Vector2i end);
	~EdgeShape() = default;

	void Draw(sf::RenderTarget& window) const override;
	void Update(sf::Vector2i begining, sf::Vector2i end, bool shallChangePosition = false);
	void FillWithDefinedColor(DefinedColor color) override;
	
	const sf::Vector2i GetPosition() const override;
	const sf::Vector2i GetEndPosition() const;

	const int GetBeginingIndex() const;
	const int GetEndIndex() const;

	bool Select(sf::Vector2i& mousePos) override;
};