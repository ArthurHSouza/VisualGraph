#include "NodeCircle.hpp"
#include <iostream>
#include <stdexcept>
#include "AssetManager.hpp"

size_t NodeCircle::count = 0;

NodeCircle::NodeCircle(sf::Vector2i position):
	position{position}, index{count++}
{

	circle.setRadius(50);
	circle.setFillColor(sf::Color::White);
	circle.setOutlineThickness(5);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOrigin(circle.getGlobalBounds().getSize() / 2.f);
	circle.setPosition(sf::Vector2f(position));

	indexText.setString(std::to_string(index));
	indexText.setFont(AssetManager<sf::Font>::Get("assets/Square.ttf"));
	indexText.setOrigin(indexText.getGlobalBounds().getSize()/2.f + indexText.getGlobalBounds().getPosition());
	indexText.setFillColor(sf::Color::Black);
	indexText.setPosition(sf::Vector2f(position));

}

void NodeCircle::Draw(sf::RenderWindow& window) const
{
	window.draw(circle);
	window.draw(indexText);
}

bool NodeCircle::SelectNode(sf::Vector2i&& mousePos)
{
	sf::Rect<float> mouseRec(sf::Vector2f(mousePos), sf::Vector2f(1,1));
	if (circle.getGlobalBounds().intersects(mouseRec))
	{
		isSelected = !isSelected;
		if (isSelected)
		{
			circle.setFillColor(sf::Color::Red);
		}
		else
		{
			circle.setFillColor(sf::Color::White);
		}
	}
	return isSelected;
}


bool NodeCircle::Intersects(sf::FloatRect rect)
{
	return circle.getGlobalBounds().intersects(rect);
}


void NodeCircle::SetAsNotSelected()
{
	isSelected = false;
	circle.setFillColor(sf::Color::White);
}

void NodeCircle::setPosition(sf::Vector2i mousePosition)
{
	this->position = mousePosition;
	circle.setPosition(sf::Vector2f(position));
	indexText.setPosition(sf::Vector2f(position));

	for (auto& e : edges)
	{
		if (e.first.expired())
		{
			continue;
		}
		auto temp = e.first.lock();
		if (e.second)
		{
			temp->Update(position, temp->getEndPosition(), true);
		}
		else
		{
			temp->Update(temp->getBeginingPosition(), position);
		}
	}
}

void NodeCircle::insertEdge(std::weak_ptr<EdgeShape> edge, bool isPrimary)
{
	edges.push_back({ edge, isPrimary });
}

const size_t NodeCircle::GetIndex() const
{
	return index;
}

const sf::Vector2i NodeCircle::getPosition() const
{
	return position;
}

const bool NodeCircle::getIsSelected() const
{
	return isSelected;
}

