#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class EdgeShape 
{
private:
	sf::RectangleShape arrowRect;
	sf::Vector2i position;
	sf::Vector2i size;
public:
	EdgeShape(sf::Vector2i begining, sf::Vector2i end);
	~EdgeShape() = default;

	void Draw(sf::RenderTarget& window);
	void rotate()
	{
		arrowRect.rotate(15);
		std::cout << "rotation " << arrowRect.getRotation() << "\n";
	}
};