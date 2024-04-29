#include "VisualObject.hpp"

sf::Color ColorPallet::darkBlue = sf::Color(0, 0, 128);
sf::Color ColorPallet::petrolBlue = sf::Color(0, 47, 168);
sf::Color ColorPallet::turquoiseBlue = sf::Color(0, 255, 255);
sf::Color ColorPallet::ceruleanBlue = sf::Color(0, 127, 255);
sf::Color ColorPallet::celestBlue = sf::Color(50, 153, 204);
sf::Color ColorPallet::darkGreen = sf::Color(0, 128, 0);
sf::Color ColorPallet::forestGreen = sf::Color(31, 73, 26);
sf::Color ColorPallet::darkGray = sf::Color(54, 54, 54);
sf::Color ColorPallet::burgundy = sf::Color(128, 0, 32);
sf::Color ColorPallet::carminRed = sf::Color(220, 53, 69);
sf::Color ColorPallet::wineRed = sf::Color(128, 0, 32);

VisualObject::VisualObject(sf::Vector2i position, const float size, sf::Color defaultColor) :
	position{position}, size{size}, defaultColor{defaultColor}
{
}