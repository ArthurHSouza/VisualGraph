#pragma once
#include "VisualObject.hpp"
#include <string>
#include <SFML/Graphics.hpp>

class VisualText : public VisualObject
{
private:
	sf::Text text;
public:
	VisualText(std::string textStr, sf::Vector2f position = sf::Vector2f(), unsigned int charSize = 30, sf::Color color = sf::Color::Black);
	~VisualText() = default;

	VisualText& operator=(const VisualText& other)
	{
		this->text = other.text;
		return *this;
	}

	void Draw(sf::RenderTarget& window) const;
	void SetPosition(sf::Vector2i position);
	void SetRotation(float rotation);
	void SetColor(sf::Color);
	const sf::Vector2i GetPosition() const override;
};


