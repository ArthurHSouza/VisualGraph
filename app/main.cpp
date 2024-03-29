#include <SFML/Graphics.hpp>
#include <vector>
#include <forward_list>
#include <array>
#include <string>
#include <memory>
#include "NodeCircle.hpp"
#include "EdgeShape.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include <iostream>

int main()
{
	std::vector<NodeCircle> nodesCircle;
	std::forward_list<std::shared_ptr<EdgeShape>> edgesShape;

	auto window = sf::RenderWindow{ { 1920u, 1080u}, "CMake SFML Project" };
	window.setFramerateLimit(144);
	Camera cam(window);

	InputManager inputManager(window, cam, nodesCircle, edgesShape);

	while (window.isOpen())
	{
		window.setView(cam.GetView());

		inputManager.Update();

		window.clear(sf::Color::White);

		for (auto& e : edgesShape)
		{
			e->Draw(window);
		}
		for (auto& node : nodesCircle)
		{
			node.Draw(window);
		}

		window.display();
	}

	return 0;
}