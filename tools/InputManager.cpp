#include "InputManager.hpp"
#include "Graph.hpp"
#include <stack>
#include "GraphHandler.hpp"
#include <cctype>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std::chrono_literals;

InputManager::InputManager(sf::RenderWindow& window, Camera& cam, std::optional<VisualText>& text,
	std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges) :
	window{ window }, cam{ cam }, text{text}, nodes{nodes}, edges{edges}
{
}

void InputManager::AddNodeOnPosition(sf::Vector2i& position)
{
	sf::Rect<float> tempRect(sf::Vector2f(position), sf::Vector2f(2, 2));
	//Cannot have to nodes on the same position
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

	//Deleting all the linked edges
	for (auto& e : edegesAdress)
	{
		std::erase_if(edges,
			[&e](auto element) {return &*element == &*e; });
	}

	//Deleting the node itself
	nodes.erase(nodes.begin() + index);

	if (nodes.empty())
	{
		deleteMode = false;
	}
	//Updating the indexes
	else
	{
		NodeCircle::ClearIndexCounter();
		for (auto& n : nodes)
		{
			n.UpdateIndex();
		}
	}

	return;
}

void InputManager::AddEdge(NodeCircle& begining, NodeCircle end)
{
	float weight = 0.f;
	bool willHaveText = true;
	//Cannot have an edge that starts and ends at the same position
	for (auto& e : edges)
	{
		if (e->GetPosition() == begining.GetPosition() && e->GetEndPosition() == end.GetPosition())
		{
			return;
		}
		else if (e->GetPosition() == end.GetPosition() && e->GetEndPosition() == begining.GetPosition())
		{
			willHaveText = false;
			weight = e->GetWeight();
		}
	}

	if(willHaveText)
	{
		isTyping.store(true);
		while (isTyping.load())
		{
			std::this_thread::sleep_for(50ms);
		}

		if(!text->GetString().empty() && text->GetString() != "\n")
			weight = std::stof(text->GetString().substr(0,5));
		else
		{
			for (auto& v : nodes)
				v.SetAsNotSelected();
			selectedNodeIndex.clear();
			text.reset();
			return;
		}
		text.reset();
	}

	edges.emplace_front(std::make_shared<EdgeShape>(begining.GetIndex(), end.GetIndex(),
		begining.GetPosition(), end.GetPosition(), weight, willHaveText));
	//Updating the linked nodes to have ref of this new edge
	nodes.at(selectedNodeIndex.front()).InsertEdge(edges.front());

	nodes.at(selectedNodeIndex.back()).InsertEdge(edges.front());
	for (auto& v : nodes)
		v.SetAsNotSelected();
	selectedNodeIndex.clear();
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
	if(timeHolding.has_value())
		timeHolding.reset();
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
	//Drag the camera
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		isDragging = true;
	}
	//Add nodes
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (deleteMode) return;
		AddNodeOnPosition(mousePosition);
	}
	//Make a node/edge selection
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (deleteMode)
		{
			DeleteEdge();
		}

		for (size_t i = 0; i < nodes.size(); i++)
		{
			if (nodes.at(i).Select(mousePosition))
			{
				if (std::ranges::find(selectedNodeIndex, i) != selectedNodeIndex.end())
				{
					continue;
				}
				if (deleteMode)
				{
					DeleteNode(i);
					return;
				}
				
				selectedNodeIndex.push_back(i);
			}
		}

		//Move the node
		if (selectedNodeIndex.size() == 1)
		{
			if (!nodes.at(selectedNodeIndex.at(0)).GetIsSelected())
			{
				selectedNodeIndex.clear();
				return;
			}
			if(!timeHolding.has_value())
				timeHolding.emplace();
			holding = true;
			return;
		}
		//Adding edge
		if (selectedNodeIndex.size() == 2)
		{
			//Type allowed
			std::thread inputTextThread(&InputManager::AddEdge, this, 
				std::ref(nodes.at(selectedNodeIndex.front())), nodes.at(selectedNodeIndex.back()));
			inputTextThread.detach();
		}
	}
}

void InputManager::KeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
	//Delete all the nodes and edges
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		NodeCircle::ClearIndexCounter();
		nodes.clear();
		edges.clear();
	}
	//Toogle the delete mode
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		deleteMode = !deleteMode;
		if (deleteMode)
		{
			for (auto& n : nodes)
			{
				n.SetAsNotSelected();
				n.FillWithDefinedColor(SelectableVisualObject::DefinedColor::DeleteColor);
			}
			for (auto& e : edges) e->FillWithDefinedColor(SelectableVisualObject::DefinedColor::DeleteColor);
		}
		else
		{
			for (auto& n : nodes) n.FillWithDefinedColor(SelectableVisualObject::DefinedColor::DefaultColor);
			for (auto& e : edges) e->FillWithDefinedColor(SelectableVisualObject::DefinedColor::DefaultColor);
		}
	}
	//Take a screenshot
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
	//BFS
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
	{
		if (!selectedNodeIndex.empty())
		{
			gh::BFS(selectedNodeIndex.at(0), nodes, edges);
			for (auto& v : nodes)
				v.SetAsNotSelected();
			selectedNodeIndex.clear();
		}
		else
			text = VisualText("You do not selected a node\n", (sf::Vector2f)(window.getSize()) / 2.f, true, 60,
				ColorPallet::wineRed, 2, ColorPallet::carminRed);
	}
	//DFS
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!selectedNodeIndex.empty())
		{
			gh::DFS(selectedNodeIndex.at(0), nodes, edges);
			for (auto& v : nodes)
				v.SetAsNotSelected();
			selectedNodeIndex.clear();
		}
		else
			text = VisualText("You do not selected a node\n", (sf::Vector2f)(window.getSize()) / 2.f, true, 60,
				ColorPallet::wineRed, 2, ColorPallet::carminRed);
	}
	//TopSort
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		gh::TopologicalSort(nodes, edges);
		for (auto& v : nodes)
			v.SetAsNotSelected();
		selectedNodeIndex.clear();
	}
	//SCC
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{	
		gh::SCC(nodes, edges);
		for (auto& v : nodes)
			v.SetAsNotSelected();
		selectedNodeIndex.clear();
	}
	//Dijkstra & BellmanFord
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if (!selectedNodeIndex.empty())
		{
			gh::ShortestPath(selectedNodeIndex.at(0), nodes, edges);
			for (auto& v : nodes)
				v.SetAsNotSelected();
			selectedNodeIndex.clear();
		}
		else
			text = VisualText("You do not selected a node\n", (sf::Vector2f)(window.getSize()) / 2.f, true, 60,
				ColorPallet::wineRed, 2, ColorPallet::carminRed);
	}
	//Prim MST
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		gh::MinimumST(nodes, edges);
		for (auto& v : nodes)
			v.SetAsNotSelected();
		selectedNodeIndex.clear();
	}
}

void InputManager::Update()
{
	for (; window.pollEvent(event);)
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
		else if (isTyping.load())
		{
			TextInput();
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

	if (holding && !deleteMode && timeHolding.has_value() && timeHolding->getElapsedTime().asSeconds() > timeToEdit)
	{
		editMode = true;
		nodes.at(selectedNodeIndex.front()).SetPosition(mousePosition);
	}
}

void InputManager::TextInput()
{
	if(!text.has_value())
		text = VisualText("Type the edge weight\n", (sf::Vector2f)(window.getSize()) / 2.f, true, 60, 
			ColorPallet::petrolBlue,2, ColorPallet::darkBlue);

	if (event.type == sf::Event::TextEntered)
	{
		if(std::isdigit(event.text.unicode) || event.text.unicode == '.' || event.text.unicode == '-')
			text->AddChar(event.text.unicode);
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::BackSpace)
			text->PopChar();
		if (event.key.code == sf::Keyboard::Return)
		{
			text->RemoveUntilChar('\n');
			isTyping.store(false);
		}
	}
}

