#include "Camera.hpp"

Camera::Camera(sf::RenderWindow& window)
{
	sf::Vector2f windowSize = sf::Vector2f(window.getSize());
	view.setSize(windowSize);
	view.setCenter(windowSize / 2.f);
	originalViewSize = view.getSize();
}


void Camera::Zoom(const float& delta)
{
	if (delta < 0 && (view.getSize().x / originalViewSize.x) < maxZoomOut)
	{
		view.zoom(1.1f);
	}
	else  if (delta > 0 && (view.getSize().x / originalViewSize.x) > maxZoomIn)
	{
		view.zoom(0.9f);
	}
}

void Camera::DraggingCamera(sf::Vector2i mousePosition, sf::Vector2i previusMousePosition)
{
	const sf::Vector2f delta = sf::Vector2f(mousePosition - previusMousePosition);
	view.move(-delta);
}

void Camera::SetSize(int x, int y)
{
	view.setSize(x, y);
}

const sf::View Camera::GetView() const
{
	return view;
}