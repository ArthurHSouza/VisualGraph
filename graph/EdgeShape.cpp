#include "EdgeShape.hpp"
#include <numbers>

EdgeShape::EdgeShape(sf::Vector2i begining, sf::Vector2i end)
{
	float difX = std::abs(end.x - begining.x);
	float dist = std::sqrt(std::pow(difX, 2) + std::pow(end.y - begining.y, 2));

	arrowRect.setSize(sf::Vector2f(10.f,dist));
	arrowRect.setOrigin(
		arrowRect.getGlobalBounds().getSize().x/2.f, 
		arrowRect.getGlobalBounds().getSize().y
	);
	arrowRect.setPosition(sf::Vector2f(begining));
	arrowRect.setFillColor(sf::Color::White);

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

void EdgeShape::Draw(sf::RenderTarget& window)
{
	window.draw(arrowRect);
}
