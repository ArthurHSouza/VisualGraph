#include "InputManager.hpp"

InputManager::InputManager(sf::RenderWindow& window, std::vector<NodeCircle>& nodes, std::list<EdgeShape>& edges) :
    window{window}, nodes{nodes}, edges{edges}
{
}

void InputManager::AddNodeOnPosition(sf::Vector2i&& position)
{
    sf::Rect<float> tempRect(sf::Vector2f(position), sf::Vector2f(2, 2));
    for (auto& i : nodes)
    {
        if (i.Intersects(tempRect))
            return;
    }
    nodes.emplace_back(position);
}

void InputManager::AddEdge(sf::Vector2i beginingPosition, sf::Vector2i endPosition)
{
    for (auto& e : edges)
    {
        if (e.getBeginingPosition() == beginingPosition && e.getEndPosition() == endPosition)
        {
            return;
        }
    }
    edges.emplace_back(beginingPosition, endPosition);

    nodes.at(selectedNodeIndex.front()).insertEdge(edges.back(), true);
    nodes.at(selectedNodeIndex.back()).insertEdge(edges.back(), false);
}

void InputManager::MouseButtonRelease()
{
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        AddNodeOnPosition(sf::Mouse::getPosition(window));
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        selectedNodeIndex.clear();
        for (auto& n : nodes)
        {
            if (n.SelectNode(sf::Mouse::getPosition(window)))
            {
                timeHolding.restart();
                selectedNodeIndex.push_back(n.GetIndex());
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
                nodes.at(selectedNodeIndex.front()).getPosition(),
                nodes.at(selectedNodeIndex.back()).getPosition()
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
    if (holding && timeHolding.getElapsedTime().asSeconds() > timeToEdit)
    {
        editMode = true;
        nodes.at(selectedNodeIndex.front()).setPosition(sf::Mouse::getPosition(window));
    }
}

