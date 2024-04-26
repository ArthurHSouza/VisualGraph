#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class VisualText
{
private:
	sf::Text text;
public:
	VisualText(std::string textStr, sf::Vector2f position, unsigned int charSize = 30, sf::Color color = sf::Color::Black);
	~VisualText() = default;

	void Draw(sf::RenderTarget& window) const;
	void SetPosition(sf::Vector2i position);
};


