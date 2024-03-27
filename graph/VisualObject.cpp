#include "VisualObject.hpp"

VisualObject::VisualObject(sf::Vector2i position, const float size, sf::Color defaultColor, sf::Color selectedColor, sf::Color deleteColor) :
	position{position}, size{size}, defaultColor{defaultColor}, selectedColor{selectedColor}, deleteColor{deleteColor}
{
}