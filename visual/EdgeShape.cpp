#include "EdgeShape.hpp"
#include <numbers>
#include <cmath>

EdgeShape::EdgeShape(int begningIndex, int endIndex, sf::Vector2i begining, sf::Vector2i end) :
	VisualObject(begining, 10.f, sf::Color::Black, sf::Color::Blue, sf::Color::Red), 
	begningIndex{begningIndex}, endIndex{endIndex}, endPosition{end}
{
	collisionPoint.setSize(sf::Vector2f(20.f,20.f));
	collisionPoint.setOrigin(collisionPoint.getGlobalBounds().getSize() / 2.f);
	collisionPoint.setFillColor(deleteColor);

	int difX = std::abs(end.x - begining.x);
	float dist = std::sqrtf(std::pow<int>(difX, 2) + std::pow<int>(end.y - begining.y, 2));


	arrowRect.setSize(sf::Vector2f(size,dist));
	arrowRect.setOrigin(
		arrowRect.getGlobalBounds().getSize().x/2.f, 
		arrowRect.getGlobalBounds().getSize().y
	);
	arrowRect.setPosition(sf::Vector2f(begining));
	arrowRect.setFillColor(defaultColor);

	float rotationDegrees = asinf(difX / dist) * 180.f/std::numbers::pi_v<float>;
	if (end.y < begining.y && end.x < begining.x)
	{
		rotationDegrees *= -1;
	}
	else if (end.y > begining.y && end.x < begining.x)
	{
		rotationDegrees -= 180;
	}
	else if (end.y > begining.y && end.x > begining.x)
	{
		rotationDegrees = 180 - rotationDegrees;
	}
	
	arrowRect.setRotation(rotationDegrees);

	float targetX = std::lerp(position.x, endPosition.x, 0.5f);
	float targetY = std::lerp(position.y, endPosition.y, 0.5f);
	collisionPoint.setPosition(targetX, targetY);
}

void EdgeShape::Draw(sf::RenderTarget& window) const
{
	window.draw(arrowRect);
	if(drawCollisionPoint)
		window.draw(collisionPoint);
}

void EdgeShape::Update(sf::Vector2i begining, sf::Vector2i end, bool shallChangePosition)
{
	position = begining;
	endPosition = end;
	if (shallChangePosition)
	{
		arrowRect.setPosition(sf::Vector2f(begining));
	}
	int difX = std::abs(end.x - begining.x);
	float dist = sqrtf(std::pow(difX, 2) + std::pow(end.y - begining.y, 2));
	
	arrowRect.setScale(1, dist / arrowRect.getSize().y);

	float rotationDegrees = asinf(difX / dist) * 180.f / std::numbers::pi_v<float>;
	if ((end.y == begining.y || end.y < begining.y) && end.x < begining.x)
	{
		rotationDegrees *= -1;
	}
	else if (end.y > begining.y && (end.x == begining.x || end.x < begining.x))
	{
		rotationDegrees -= 180;
	}
	else if (end.y > begining.y && end.x > begining.x)
	{
		rotationDegrees = 180 - rotationDegrees;
	}
	
	arrowRect.setRotation(rotationDegrees);

	float targetX = std::lerp(position.x, endPosition.x, 0.5f);
	float targetY = std::lerp(position.y, endPosition.y, 0.5f);
	collisionPoint.setPosition(targetX, targetY);
}

void EdgeShape::FillWithDefinedColor(DefinedColor color)
{
	drawCollisionPoint = false;
	switch (color)
	{
	case VisualObject::DefinedColor::DefaultColor:
		arrowRect.setFillColor(defaultColor);
		break;
	case VisualObject::DefinedColor::SelectedColor:
		arrowRect.setFillColor(selectedColor);
		break;
	case VisualObject::DefinedColor::DeleteColor:
		drawCollisionPoint = true;
		arrowRect.setFillColor(deleteColor);
		break;
	default:
		break;
	}
}

const sf::Vector2i EdgeShape::GetPosition() const
{
	return position;
}

const sf::Vector2i EdgeShape::GetEndPosition() const
{
	return endPosition;
}

const int EdgeShape::GetBeginingIndex() const
{
	return begningIndex;
}

const int EdgeShape::GetEndIndex() const
{
	return endIndex;
}

bool EdgeShape::Select(sf::Vector2i& mousePos)
{
	sf::Rect<float> mouseRec(sf::Vector2f(mousePos), sf::Vector2f(1, 1));
	return collisionPoint.getGlobalBounds().intersects(mouseRec);
}
