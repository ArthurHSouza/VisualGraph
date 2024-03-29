#include "InputManager.hpp"

InputManager::InputManager(sf::RenderWindow& window, Camera& cam,std::vector<NodeCircle>& nodes, std::list<std::shared_ptr<EdgeShape>>& edges) :
    window{window}, cam{cam}, nodes{nodes}, edges{edges}
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
    return;
}

void InputManager::AddEdge(sf::Vector2i beginingPosition, sf::Vector2i endPosition)
{
    for (auto& e : edges)
    {
        if (e->GetPosition() == beginingPosition && e->GetEndPosition() == endPosition)
        {
            return;
        }
    }

    edges.emplace_back(std::make_shared<EdgeShape>(beginingPosition, endPosition));

    nodes.at(selectedNodeIndex.front()).insertEdge(edges.back());
    nodes.at(selectedNodeIndex.back()).insertEdge(edges.back());
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
                nodes.at(selectedNodeIndex.front()).GetPosition(),
                nodes.at(selectedNodeIndex.back()).GetPosition()
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
            for (auto& n : nodes) n.FillWithDefinedColor(VisualObject::DefinedColor::DeleteColor);
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
            if (isDragging) {
                cam.DraggingCamera(mousePosition, previousMousePosition);
            }
            previousMousePosition = mousePosition;
        }
    }

    if (holding && !deleteMode && timeHolding.getElapsedTime().asSeconds() > timeToEdit)
    {
        editMode = true;
        nodes.at(selectedNodeIndex.front()).SetPosition(mousePosition);
    }
}

    