#include "AssetManager.hpp"
#include "VisualText.hpp"
#include <exception>
#include <iostream>
VisualText::VisualText(std::string textStr, sf::Vector2f position, bool alignCenter,unsigned int charSize, 
	sf::Color color, unsigned int outlineSize, sf::Color outineColor) :
	VisualObject((sf::Vector2i)position, charSize, color)
{
	text = sf::Text(
		textStr,
		AssetManager<sf::Font>::Get("assets/Square.ttf"),
		charSize
	);
	if(alignCenter)
		text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getGlobalBounds().getPosition());
	text.setFillColor(color);
	text.setPosition(position);

	if (outlineSize != 0)
	{
		text.setOutlineThickness(outlineSize);
		text.setOutlineColor(outineColor);
	}
}

void VisualText::Draw(sf::RenderTarget& window) const
{
	window.draw(text);
}

void VisualText::SetPosition(sf::Vector2i position)
{
	position = position;
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

void VisualText::AddChar(const char& c)
{
	text.setString(text.getString() + c);
	text.setPosition((sf::Vector2f)position);
}

void VisualText::PopChar()
{
	std::string temp = text.getString();
	if (*temp.rbegin() == '\n')
		return;
	temp.pop_back();
	text.setString(temp);
	text.setPosition((sf::Vector2f)position);
}

void VisualText::RemoveUntilChar(const char& c)
{
	std::string temp = text.getString();
	std::string::size_type it = temp.find(c);
	if (it == std::string::npos)
		throw(std::runtime_error("Cannot find this char"));
	temp.erase(temp.begin(), temp.begin() + it);
	text.setString(temp);
	text.setPosition((sf::Vector2f)position);
}

VisualText& VisualText::operator=(const VisualText& other)
{
	this->text = other.text;
	this->alignCenter = other.alignCenter;
	this->position = other.position;
	this->size = other.size;

	return *this;
}

VisualText& VisualText::operator=(const std::string& str)
{
	text = sf::Text(
		str,
		AssetManager<sf::Font>::Get("assets/Square.ttf"),
		size
	);
	if(alignCenter)
		text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getGlobalBounds().getPosition());
	text.setFillColor(defaultColor);
	text.setPosition((sf::Vector2f)position);

	return *this;
}

const std::string VisualText::GetString() const
{
	return text.getString();
}