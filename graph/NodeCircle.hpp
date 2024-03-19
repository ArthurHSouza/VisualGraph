#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class NodeCircle
{
private:
	sf::Vector2i position;
	sf::CircleShape circle;
	sf::Text indexText;

public:
	static size_t index;
	NodeCircle(sf::Vector2i position);
	~NodeCircle() = default;

	void DrawShape(sf::RenderWindow& window) const;
};
