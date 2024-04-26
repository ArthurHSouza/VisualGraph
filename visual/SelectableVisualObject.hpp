#pragma once 
#include "VisualObject.hpp"

class SelectableVisualObject : public VisualObject
{
protected:
	const sf::Color selectedColor;
	const sf::Color deleteColor;
public:
	enum class DefinedColor
	{
		DefaultColor, SelectedColor, DeleteColor
	};

	SelectableVisualObject(sf::Vector2i position, const float size, sf::Color defaultColor, sf::Color selectedColor, sf::Color deleteColor);
	virtual ~SelectableVisualObject() = default;

	virtual void FillWithDefinedColor(DefinedColor color) = 0;
	virtual bool Select(sf::Vector2i& mousePos) = 0;
};