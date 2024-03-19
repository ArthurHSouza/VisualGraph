#include "NodeCircle.hpp"
#include <iostream>
#include <stdexcept>
#include "AssetManager.hpp"

size_t NodeCircle::index = 0;
NodeCircle::NodeCircle(sf::Vector2i position):
	position{position}
{

	circle.setRadius(50);
	circle.setFillColor(sf::Color::White);
	circle.setOutlineThickness(5);
	circle.setOutlineColor(sf::Color::Blue);
	circle.setOrigin(circle.getGlobalBounds().getSize() / 2.f);
	circle.setPosition(sf::Vector2f(position));

	indexText.setString(std::to_string(index++));
	indexText.setOrigin(indexText.getGlobalBounds().getSize() / 2.f);
	indexText.setFont(AssetManager<sf::Font>::Get("assets/Square.ttf"));
	indexText.setColor(sf::Color::Black);
	indexText.setPosition(sf::Vector2f(position));
}

void NodeCircle::DrawShape(sf::RenderWindow& window) const
{
	window.draw(circle);
	window.draw(indexText);
}
