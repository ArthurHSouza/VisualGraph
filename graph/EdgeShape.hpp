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
	void Update(sf::Vector2i begining, sf::Vector2i end, bool shallChangePosition = false);
	const sf::Vector2i getBeginingPosition() const;
	const sf::Vector2i getEndPosition() const;

	template <typename T> 
	int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	void ChangeColor()
	{
		arrowRect.setFillColor(sf::Color::Blue);
	}
	void updatePos()
	{

		arrowRect.scale(1.1, 1.1);
 		//arrowRect.setSize(arrowRect.getSize() + sf::Vector2f(50,20));
	
	}
	void updatePosY()
	{
		arrowRect.setOrigin(
			arrowRect.getGlobalBounds().getSize().x / 2.f,
			arrowRect.getGlobalBounds().getSize().y / 2.f);
		arrowRect.setSize(arrowRect.getSize() + sf::Vector2f(50, 0));
	}
};