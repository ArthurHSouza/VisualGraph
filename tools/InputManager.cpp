#include "InputManager.hpp"
#include "Graph.hpp"

InputManager::InputManager(sf::RenderWindow& window, Camera& cam, std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges) :
	window{ window }, cam{ cam }, nodes{ nodes }, edges{ edges }
{
}

void InputManager::AddNodeOnPosition(sf::Vector2i& position)
{
	sf::Rect<float> tempRect(sf::Vector2f(position), sf::Vector2f(2, 2));
	for (auto& i : nodes)
	{
		if (i.Intersects(tempRect))
			return;
	}
	nodes.emplace_back(position);
}

void InputManager::DeleteNode(size_t index)
{
	auto edegesAdress = nodes.at(index).GetLinkedEdges();

	for (auto& e : edegesAdress)
	{
		std::erase_if(edges,
			[&e](auto element) {return &*element == &*e; });
	}

	nodes.erase(nodes.begin() + index);

	if (nodes.empty())
	{
		deleteMode = false;
	}

	return;
}

void InputManager::AddEdge(NodeCircle& begining, NodeCircle end)
{
	for (auto& e : edges)
	{
		if (e->GetPosition() == begining.GetPosition() && e->GetEndPosition() == end.GetPosition())
		{
			return;
		}
	}

	edges.emplace_front(std::make_shared<EdgeShape>(begining.GetIndex(), end.GetIndex(), 
		begining.GetPosition(), end.GetPosition()));

	nodes.at(selectedNodeIndex.front()).insertEdge(edges.front());
	nodes.at(selectedNodeIndex.back()).insertEdge(edges.front());
}

void InputManager::DeleteEdge()
{
	std::erase_if(edges,
		[&](std::shared_ptr<EdgeShape>& e) {
			return  e->Select(mousePosition);
		});
}

void InputManager::MouseButtonRelease()
{
	isDragging = false;
	holding = false;
	if (editMode)
	{
		editMode = false;
		if (!selectedNodeIndex.empty())
		{
			nodes.at(selectedNodeIndex.front()).SetAsNotSelected();
			selectedNodeIndex.clear();
		}
	}
}

void InputManager::MouseButtonInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		isDragging = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (deleteMode) return;
		AddNodeOnPosition(mousePosition);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		selectedNodeIndex.clear();

		if (deleteMode)
		{
			DeleteEdge();
		}

		for (size_t i = 0; i < nodes.size(); i++)
		{
			if (nodes.at(i).Select(mousePosition))
			{
				if (deleteMode)
				{
					DeleteNode(i);
				}
				timeHolding.restart();
				selectedNodeIndex.push_back(i);
			}
		}

		if (selectedNodeIndex.size() == 1)
		{
			holding = true;
			return;
		}

		if (selectedNodeIndex.size() == 2)
		{
			AddEdge(
				nodes.at(selectedNodeIndex.front()),
				nodes.at(selectedNodeIndex.back())
			);
			for (auto& v : nodes) v.SetAsNotSelected();
		}
	}
}

void InputManager::KeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		NodeCircle::count = 0;
		nodes.clear();
		edges.clear();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		deleteMode = !deleteMode;
		if (deleteMode)
		{
			for (auto& n : nodes)
			{
				n.SetAsNotSelected();
				n.FillWithDefinedColor(VisualObject::DefinedColor::DeleteColor);
			}
			for (auto& e : edges) e->FillWithDefinedColor(VisualObject::DefinedColor::DeleteColor);
		}
		else
		{
			for (auto& n : nodes) n.FillWithDefinedColor(VisualObject::DefinedColor::DefaultColor);
			for (auto& e : edges) e->FillWithDefinedColor(VisualObject::DefinedColor::DefaultColor);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		sf::Texture texture;
		const std::string fileName{ "ScreenshotGraph.png" };
		texture.create(window.getSize().x, window.getSize().y);
		texture.update(window);
		if (texture.copyToImage().saveToFile(fileName))
		{
			std::cout << "screenshot saved to " << fileName << std::endl;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
	{
		Graph g = Graph(nodes.size());
		for (const auto& e : edges)
		{
			g.AddEdges(e->GetBeginingIndex(), e->GetEndIndex());
		}
		g.BFS(0);
	}
}

void InputManager::Update()
{
	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			cam.SetSize(event.size.width, event.size.height);
		}
		else if (event.type == sf::Event::MouseWheelScrolled)
		{
			cam.Zoom(event.mouseWheelScroll.delta);
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			MouseButtonRelease();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			MouseButtonInput();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			KeyboardInput();
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			mousePosition = (sf::Vector2i)window.mapPixelToCoords(sf::Mouse::getPosition(window));
			sf::Vector2i mousePositionPixel = window.mapCoordsToPixel((sf::Vector2f)mousePosition);
			if (isDragging) {

				cam.DraggingCamera(mousePositionPixel, previousMousePosition);
			}
			previousMousePosition = mousePositionPixel;
		}
	}

	if (holding && !deleteMode && timeHolding.getElapsedTime().asSeconds() > timeToEdit)
	{
		editMode = true;
		nodes.at(selectedNodeIndex.front()).SetPosition(mousePosition);
	}
}

