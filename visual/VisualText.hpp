#pragma once
#include "VisualObject.hpp"
#include <string>
#include <SFML/Graphics.hpp>

//A text representation
class VisualText : public VisualObject
{
private:
	sf::Text text;
	bool alignCenter;
public:
	VisualText(std::string textStr, sf::Vector2f position = sf::Vector2f(), bool alignCenter = true, unsigned int charSize = 30,
		sf::Color color = sf::Color::Black, unsigned int outlineSize = 0u, sf::Color outineColor = sf::Color::Black);
	~VisualText() = default;

	void Draw(sf::RenderTarget& window) const;
	void SetPosition(sf::Vector2i position);
	void SetRotation(float rotation);
	void SetColor(sf::Color);
	const sf::Vector2i GetPosition() const override;
	void AddChar(const char& c);
	void PopChar();
	void RemoveUntilChar(const char& c);
	VisualText& operator=(const VisualText& other);
	VisualText& operator=(const std::string& str);
	const std::string GetString() const;
};


