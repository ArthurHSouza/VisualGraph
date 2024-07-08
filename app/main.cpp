#include "Camera.hpp"
#include "EdgeShape.hpp"
#include "InputManager.hpp"
#include "NodeCircle.hpp"
#include <array>
#include <forward_list>
#include <iostream>
#include <memory>
#include <optional>
#include <SFML/Graphics.hpp>
#include <vector>

//#include <atomic>
//#include <thread>

//void Update(InputManager& inputManager, std::atomic<bool>& running)
//{
//	while (running.load())
//	{
//		std::cout << "opa\n";
//		inputManager.Update();
//	}
//}

int main()
{
	std::optional<VisualText> text;
	std::vector<NodeCircle> nodesCircle;
	std::forward_list<std::shared_ptr<EdgeShape>> edgesShape;
	/*std::atomic<bool> running(true);*/

	auto window = sf::RenderWindow{ { 1920u, 1080u}, "CMake SFML Project" };
	window.setFramerateLimit(144);
	Camera cam(window);

	InputManager inputManager(window, cam, text,nodesCircle, edgesShape);

	//std::thread inputThread (Update, std::ref(inputManager), std::ref(running));
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
		if (text.has_value())
		{
			text->Draw(window);
		}
		window.display();
	}
	return 0;
}
