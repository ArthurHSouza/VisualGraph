#pragma once
#include <SFML/Graphics.hpp>

class VisualObject
{
protected:
	sf::Vector2i position;
	const float size;
	const sf::Color defaultColor;
	const sf::Color selectedColor;
	const sf::Color deleteColor;
public:
	enum class DefinedColor
	{
		DefaultColor, SelectedColor, DeleteColor
	};
	VisualObject(sf::Vector2i position, const float size, sf::Color defaultColor, sf::Color selectedColor, sf::Color deleteColor);
	virtual ~VisualObject() = default;

	virtual void Draw(sf::RenderTarget& window) const = 0;
	virtual const sf::Vector2i GetPosition() const = 0;
	virtual void FillWithDefinedColor(DefinedColor color) = 0;
	virtual bool Select(sf::Vector2i&& mousePos) = 0;
};
