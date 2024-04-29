#include "EdgeShape.hpp"
#include <numbers>
#include <cmath>
#include <iostream>

EdgeShape::EdgeShape(std::size_t begningIndex, std::size_t endIndex, sf::Vector2i begining, sf::Vector2i end) :
	SelectableVisualObject(begining, 10.f, sf::Color::Black, ColorPallet::celestBlue, ColorPallet::carminRed),
	begningIndex{begningIndex}, endIndex{endIndex}, endPosition{end}, weightText(std::to_string(weight).substr(0,5))
{
	weightText.SetColor(ColorPallet::petrolBlue);

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
	UpdateWeightText();

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
	else if (endPosition.x <= position.x && endPosition.y <= position.y)
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
	else if (endPosition.x <= position.x && endPosition.y >= position.y)
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
	else if (endPosition.x >= position.x && endPosition.y >= position.y)
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

void EdgeShape::UpdateWeightText()
{
	int difX = std::abs(endPosition.x - collisionPoint.getPosition().x);
	float dist = std::sqrtf(std::pow<int>(difX, 2) + std::pow<int>(endPosition.y - collisionPoint.getPosition().y, 2));
	float rotationRadians = asinf(difX / dist) + std::numbers::pi_v<float> / 20.f;
	float rotationDegrees = asinf(difX / dist) * 180.f / std::numbers::pi_v<float>;
	sf::Vector2f textPosition;

	if (endPosition.x >= position.x && endPosition.y <= position.y)
	{
		std::cout << "antes " << rotationRadians * 180.f / std::numbers::pi_v<float> << "\n";
		rotationRadians = fabs(std::numbers::pi_v<float> / 2 - rotationRadians);
	//	rotationRadians = test;
		textPosition = sf::Vector2f(
			-dist * cosf(rotationRadians),
			dist * sinf(rotationRadians)
		);
		rotationDegrees -= 90.f;
		std::cout << "Depois " << rotationRadians * 180.f / std::numbers::pi_v<float> << "\n";
	}
	else if (endPosition.x <= position.x && endPosition.y <= position.y)
	{
		rotationRadians = std::numbers::pi_v<float> / 2.f + rotationRadians;
		textPosition = sf::Vector2f(
			-dist * cosf(rotationRadians),
			dist * sinf(rotationRadians)
		);
		rotationDegrees += 180.f;
		rotationDegrees = abs(rotationDegrees + 90 - 180);
	}
	else if (endPosition.x <= position.x && endPosition.y >= position.y)
	{
		rotationRadians = asinf(difX / dist) - std::numbers::pi_v<float> / 20.f;
		rotationRadians = fabs(std::numbers::pi_v<float> / 2.f - rotationRadians);
		textPosition = sf::Vector2f(
			dist * cosf(rotationRadians),
			-dist * sinf(rotationRadians)
		);
		rotationDegrees -= 90.f;
	}
	else if (endPosition.x >= position.x && endPosition.y >= position.y)
	{
		rotationRadians = asinf(difX / dist) - std::numbers::pi_v<float> / 20.f;
		textPosition = sf::Vector2f(
			-dist * sinf(rotationRadians),
			-dist * cosf(rotationRadians)
		);
		rotationDegrees = abs(rotationDegrees + 90 - 180);
	}
	std::cout << dist << " endPos " << endPosition.x << " " << endPosition.y << " textPosition " << textPosition.x << " " << textPosition.y << "\n";
	weightText.SetPosition( endPosition + (sf::Vector2i)textPosition);
	
	//weightText.SetRotation(rotationDegrees);
}

void EdgeShape::Draw(sf::RenderTarget& window) const
{
	window.draw(arrowRect);
	if(drawCollisionPoint)
		window.draw(collisionPoint);
	window.draw(arrowHead);
	weightText.Draw(window);
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
	UpdateWeightText();
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

const float EdgeShape::GetWeight() const
{
	return weight;
}

bool EdgeShape::Select(sf::Vector2i& mousePos)
{
	sf::Rect<float> mouseRec(sf::Vector2f(mousePos), sf::Vector2f(1, 1));
	return collisionPoint.getGlobalBounds().intersects(mouseRec);
}
