#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class EdgeShape 
{
private:
	sf::RectangleShape arrowRect;
	sf::Vector2i position;
	sf::Vector2i endPosition;
	sf::Vector2i size;
public:
	EdgeShape(sf::Vector2i begining, sf::Vector2i end);
	~EdgeShape() = default;

	void Draw(sf::RenderTarget& window);
	const sf::Vector2i getBeginingPosition() const;
	const sf::Vector2i getEndPosition() const;
};