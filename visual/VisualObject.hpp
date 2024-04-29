#pragma once
#include <SFML/Graphics.hpp>

struct ColorPallet
{
	static sf::Color darkBlue;
	static sf::Color petrolBlue;
	static sf::Color turquoiseBlue; 
	static sf::Color ceruleanBlue;
	static sf::Color celestBlue;
	static sf::Color darkGreen;
	static sf::Color forestGreen;
	static sf::Color darkGray;
	static sf::Color burgundy;
	static sf::Color carminRed;
	static sf::Color wineRed;
};

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
