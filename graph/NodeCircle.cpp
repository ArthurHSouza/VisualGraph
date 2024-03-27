#include "NodeCircle.hpp"
#include <iostream>
#include <stdexcept>
#include "AssetManager.hpp"

size_t NodeCircle::count = 0;

NodeCircle::NodeCircle(sf::Vector2i position) :
	VisualObject(position,50.f, sf::Color::White, sf::Color::Blue, sf::Color::Red), index{count++}, outlineColor{ sf::Color::Black }
{
	circle.setRadius(size);
	circle.setFillColor(defaultColor);
	circle.setOutlineThickness(size*0.1f);
	circle.setOutlineColor(outlineColor);
	circle.setOrigin(circle.getGlobalBounds().getSize() / 2.f);
	circle.setPosition(sf::Vector2f(position));

	indexText.setString(std::to_string(index));
	indexText.setFont(AssetManager<sf::Font>::Get("assets/Square.ttf"));
	indexText.setOrigin(indexText.getGlobalBounds().getSize()/2.f + indexText.getGlobalBounds().getPosition());
	indexText.setFillColor(sf::Color::Black);
	indexText.setPosition(sf::Vector2f(position));

}

void NodeCircle::Draw(sf::RenderTarget& window) const
{
	window.draw(circle);
	window.draw(indexText);
}

void NodeCircle::FillWithDefinedColor(DefinedColor color)
{
	switch (color)
	{
	case VisualObject::DefinedColor::DefaultColor:
		circle.setFillColor(defaultColor);
		break;
	case VisualObject::DefinedColor::SelectedColor:
		circle.setFillColor(selectedColor);
		break;
	case VisualObject::DefinedColor::DeleteColor:
		circle.setFillColor(deleteColor);
		break;
	default:
		break;
	}
}

bool NodeCircle::SelectNode(sf::Vector2i&& mousePos)
{
	sf::Rect<float> mouseRec(sf::Vector2f(mousePos), sf::Vector2f(1,1));
	if (circle.getGlobalBounds().intersects(mouseRec))
	{
		isSelected = !isSelected;
		if (isSelected)
		{
			circle.setFillColor(selectedColor);
		}
		else
		{
			circle.setFillColor(defaultColor);
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
			temp->Update(position, temp->GetEndPosition(), true);
		}
		else
		{
			temp->Update(temp->GetPosition(), position);
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

const sf::Vector2i NodeCircle::GetPosition() const
{
	return position;
}

const bool NodeCircle::GetIsSelected() const
{
	return isSelected;
}

