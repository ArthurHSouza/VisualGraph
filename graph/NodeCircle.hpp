#pragma once
#include <SFML/Graphics.hpp>

class NodeCircle
{
private:
	sf::Vector2i position;
	sf::CircleShape circle;
	sf::Text indexText;
	const size_t index;
	bool isSelected{ false };

public:
	static size_t count;
	NodeCircle(sf::Vector2i position);
	~NodeCircle() = default;

	void DrawShape(sf::RenderWindow& window) const;
	
	bool Intersects(sf::FloatRect rect);
	int SelectNode(sf::Vector2i&& mousePos);
	void SetAsNotSelected();
	const size_t GetIndex() const;
	const sf::Vector2i getPosition() const;
};
