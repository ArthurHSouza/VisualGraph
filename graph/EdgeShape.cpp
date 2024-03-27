#include "EdgeShape.hpp"
#include <numbers>
#include <cmath>

EdgeShape::EdgeShape(sf::Vector2i begining, sf::Vector2i end) :
	VisualObject(begining, 10.f, sf::Color::Black, sf::Color::Blue, sf::Color::Red), endPosition{end}
{
	int difX = std::abs(end.x - begining.x);
	float dist = std::sqrtf(std::pow<int>(difX, 2) + std::pow<int>(end.y - begining.y, 2));


	arrowRect.setSize(sf::Vector2f(size,dist));
	arrowRect.setOrigin(
		arrowRect.getGlobalBounds().getSize().x/2.f, 
		arrowRect.getGlobalBounds().getSize().y
	);
	arrowRect.setPosition(sf::Vector2f(begining));
	arrowRect.setFillColor(defaultColor);

	float rotationDegrees = std::asinf(difX / dist) * 180.f/std::numbers::pi_v<float>;
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
}

void EdgeShape::Draw(sf::RenderTarget& window) const
{
	window.draw(arrowRect);
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
	float dist = std::sqrtf(std::pow(difX, 2) + std::pow(end.y - begining.y, 2));
	
	arrowRect.setScale(1, dist / arrowRect.getSize().y);

	float rotationDegrees = std::asinf(difX / dist) * 180.f / std::numbers::pi_v<float>;
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
}

void EdgeShape::FillWithDefinedColor(DefinedColor color)
{
	switch (color)
	{
	case VisualObject::DefinedColor::DefaultColor:
		arrowRect.setFillColor(defaultColor);
		break;
	case VisualObject::DefinedColor::SelectedColor:
		arrowRect.setFillColor(selectedColor);
		break;
	case VisualObject::DefinedColor::DeleteColor:
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
