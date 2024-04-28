#include "EdgeShape.hpp"
#include <numbers>
#include <cmath>
#include <iostream>

EdgeShape::EdgeShape(std::size_t begningIndex, std::size_t endIndex, sf::Vector2i begining, sf::Vector2i end) :
	SelectableVisualObject(begining, 10.f, sf::Color::Black, sf::Color::Blue, sf::Color::Red),
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

	arrowHead.setPointCount(3);
	arrowHead.setFillColor(defaultColor);
	UpdateArrowHead(difX, dist);

}

void EdgeShape::UpdateArrowHead(const int& difX, const float& distance)
{
	float rotationRadians = asinf(difX / distance);
	sf::Vector2f offset1ArrowHead;
	sf::Vector2f offset2ArrowHead;
	sf::Vector2f offset3ArrowHead;
	const float distanceOtherPoints = 75.f;
	const float offsetAngle = std::numbers::pi_v<float> / 10.f;
	if (endPosition.x >= position.x && endPosition.y <= position.y)
	{
		rotationRadians = fabs(std::numbers::pi_v<float> / 2.f - rotationRadians);
		offset1ArrowHead = sf::Vector2f(
			-50.f * cosf(rotationRadians),
			50.f * sinf(rotationRadians)
		);

		offset2ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians + offsetAngle),
			distanceOtherPoints * sinf(rotationRadians + offsetAngle)
		);

		offset3ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians - offsetAngle),
			distanceOtherPoints * sinf(rotationRadians - offsetAngle)
		);
	}
	else if (endPosition.x < position.x && endPosition.y < position.y)
	{
		rotationRadians = std::numbers::pi_v<float> / 2.f + rotationRadians;
		offset1ArrowHead = sf::Vector2f(
			-50.f * cosf(rotationRadians),
			50.f * sinf(rotationRadians)
		);

		offset2ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians + offsetAngle),
			distanceOtherPoints * sinf(rotationRadians + offsetAngle)
		);

		offset3ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians - offsetAngle),
			distanceOtherPoints * sinf(rotationRadians - offsetAngle)
		);
	}
	else if (endPosition.x < position.x && endPosition.y > position.y)
	{
		rotationRadians = fabs(std::numbers::pi_v<float> / 2.f - rotationRadians);
		offset1ArrowHead = sf::Vector2f(
			50.f * cosf(rotationRadians),
			-50.f * sinf(rotationRadians)
		);

		offset2ArrowHead = sf::Vector2f(
			distanceOtherPoints * cosf(rotationRadians + offsetAngle),
			-distanceOtherPoints * sinf(rotationRadians + offsetAngle)
		);

		offset3ArrowHead = sf::Vector2f(
			distanceOtherPoints * cosf(rotationRadians - offsetAngle),
			-distanceOtherPoints * sinf(rotationRadians - offsetAngle)
		);
	}
	else if (endPosition.x > position.x && endPosition.y > position.y)
	{
		offset1ArrowHead = sf::Vector2f(
			-50.f * sinf(rotationRadians),
			-50.f * cosf(rotationRadians)
		);

		offset2ArrowHead = sf::Vector2f(
			-distanceOtherPoints * sinf(rotationRadians + offsetAngle),
			-distanceOtherPoints * cosf(rotationRadians + offsetAngle)
		);

		offset3ArrowHead = sf::Vector2f(
			-distanceOtherPoints * sinf(rotationRadians - offsetAngle),
			-distanceOtherPoints * cosf(rotationRadians - offsetAngle)
		);
	}

	arrowHead.setPoint(0, (sf::Vector2f)endPosition + offset1ArrowHead);
	arrowHead.setPoint(1, (sf::Vector2f)endPosition + offset2ArrowHead);
	arrowHead.setPoint(2, (sf::Vector2f)endPosition + offset3ArrowHead);
}

void EdgeShape::Draw(sf::RenderTarget& window) const
{
	window.draw(arrowRect);
	if(drawCollisionPoint)
		window.draw(collisionPoint);
	window.draw(arrowHead);
}

void EdgeShape::Update(sf::Vector2i begining, sf::Vector2i end, bool shallChangePosition)
{
	position = begining;
	endPosition = end;
	if (shallChangePosition)
	{
		arrowRect.setPosition(sf::Vector2f(begining));
	}
	std::size_t difX = std::abs(end.x - begining.x);
	float dist = sqrtf(std::pow(difX, 2) + std::pow(end.y - begining.y, 2));
	
	arrowRect.setScale(1, dist / arrowRect.getSize().y);

	float rotationDegrees = asinf(difX / dist) * 180.f / std::numbers::pi_v<float>;
	if (end.y <= begining.y && end.x < begining.x)
	{
		rotationDegrees *= -1;
	}
	else if (end.y > begining.y && end.x <= begining.x)
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

	UpdateArrowHead(difX, dist);
}

void EdgeShape::FillWithDefinedColor(DefinedColor color)
{
	drawCollisionPoint = false;
	switch (color)
	{
	case SelectableVisualObject::DefinedColor::DefaultColor:
		arrowRect.setFillColor(defaultColor);
		arrowHead.setFillColor(defaultColor);
		break;
	case SelectableVisualObject::DefinedColor::SelectedColor:
		arrowRect.setFillColor(selectedColor);
		arrowHead.setFillColor(selectedColor);
		break;
	case SelectableVisualObject::DefinedColor::DeleteColor:
		drawCollisionPoint = true;
		arrowRect.setFillColor(deleteColor);
		arrowHead.setFillColor(deleteColor);
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

const std::size_t EdgeShape::GetBeginingIndex() const
{
	return begningIndex;
}

const std::size_t EdgeShape::GetEndIndex() const
{
	return endIndex;
}

bool EdgeShape::Select(sf::Vector2i& mousePos)
{
	sf::Rect<float> mouseRec(sf::Vector2f(mousePos), sf::Vector2f(1, 1));
	return collisionPoint.getGlobalBounds().intersects(mouseRec);
}
