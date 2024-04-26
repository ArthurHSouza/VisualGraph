#include "SelectableVisualObject.hpp"

SelectableVisualObject::SelectableVisualObject(sf::Vector2i position, const float size,
	sf::Color defaultColor, sf::Color selectedColor, sf::Color deleteColor) :
	VisualObject(position, size, defaultColor), selectedColor{ selectedColor }, deleteColor{ deleteColor }
{
}