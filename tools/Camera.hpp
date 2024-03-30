#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
private:
	sf::View view;
	const float maxZoomIn{ 0.8f };
	const float maxZoomOut{ 4.f };
	sf::Vector2f originalViewSize;
public:
	Camera(sf::RenderWindow& window);
	~Camera() = default;

	void Zoom(const float& delta);
	void DraggingCamera(const sf::Vector2i& mousePosition, const sf::Vector2i& previusMousePosition);
	void SetSize(int x, int y);
	const sf::View GetView() const;
};
