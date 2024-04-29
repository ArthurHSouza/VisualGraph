#include "AssetManager.hpp"
#include "VisualText.hpp"

VisualText::VisualText(std::string textStr, sf::Vector2f position, unsigned int charSize, sf::Color color) :
	VisualObject((sf::Vector2i)position, charSize, color)
{
	text = sf::Text(
		textStr,
		AssetManager<sf::Font>::Get("assets/Square.ttf"),
		charSize
	);

	text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getGlobalBounds().getPosition());
	text.setFillColor(color);
	text.setPosition(position);
}

void VisualText::Draw(sf::RenderTarget& window) const
{
	window.draw(text);
}

void VisualText::SetPosition(sf::Vector2i position)
{
	text.setPosition((sf::Vector2f)position);
}

void VisualText::SetRotation(float rotation)
{
	text.setRotation(rotation);
}

void VisualText::SetColor(sf::Color color)
{
	text.setColor(color);
}

const sf::Vector2i VisualText::GetPosition() const
{
	return (sf::Vector2i)text.getPosition();
}