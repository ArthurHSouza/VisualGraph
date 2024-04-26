#include "VisualObject.hpp"

VisualObject::VisualObject(sf::Vector2i position, const float size, sf::Color defaultColor) :
	position{position}, size{size}, defaultColor{defaultColor}
{
}