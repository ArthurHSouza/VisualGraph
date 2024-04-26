#pragma once
#include <SFML/Graphics.hpp>

class VisualObject
{
protected:
	sf::Vector2i position;
	const float size;
	const sf::Color defaultColor;
public:
	VisualObject(sf::Vector2i position, const float size, sf::Color defaultColor);
	virtual ~VisualObject() = default;

	virtual void Draw(sf::RenderTarget& window) const = 0;
	virtual const sf::Vector2i GetPosition() const = 0;
};
