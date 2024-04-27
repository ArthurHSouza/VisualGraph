#include "NodeCircle.hpp"
#include <iostream>
#include <stdexcept>
#include "AssetManager.hpp"

size_t NodeCircle::count = 0;

NodeCircle::NodeCircle(sf::Vector2i position) :
	SelectableVisualObject(position, 50.f, sf::Color::White, sf::Color::Blue, sf::Color::Red), outlineColor{ sf::Color::Black }, 
	indexText(std::to_string(count), (sf::Vector2f)position), index{ count++ }
{
	circle.setRadius(size);
	circle.setFillColor(defaultColor);
	circle.setOutlineThickness(size * 0.1f);
	circle.setOutlineColor(outlineColor);
	circle.setOrigin(circle.getGlobalBounds().getSize() / 2.f);
	circle.setPosition(sf::Vector2f(position));
}

void NodeCircle::Draw(sf::RenderTarget& window) const
{
	window.draw(circle);
	indexText.Draw(window);

	if (extraText.has_value())
		extraText->Draw(window);
}

void NodeCircle::FillWithDefinedColor(DefinedColor color)
{
	switch (color)
	{
	case SelectableVisualObject::DefinedColor::DefaultColor:
		circle.setFillColor(defaultColor);
		break;
	case SelectableVisualObject::DefinedColor::SelectedColor:
		circle.setFillColor(selectedColor);
		break;
	case SelectableVisualObject::DefinedColor::DeleteColor:
		circle.setFillColor(deleteColor);
		break;
	default:
		break;
	}
}

void NodeCircle::FillOutlineWithDefinedColor(DefinedColor color)
{
	switch (color)
	{
	case SelectableVisualObject::DefinedColor::DefaultColor:
		circle.setOutlineColor(outlineColor);
		break;
	case SelectableVisualObject::DefinedColor::SelectedColor:
		circle.setOutlineColor(selectedColor);
		break;
	case SelectableVisualObject::DefinedColor::DeleteColor:
		circle.setOutlineColor(deleteColor);
		break;
	default:
		break;
	}
}
bool NodeCircle::Select(sf::Vector2i& mousePos)
{
	sf::Rect<float> mouseRec(sf::Vector2f(mousePos), sf::Vector2f(1, 1));
	
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

void NodeCircle::SetPosition(sf::Vector2i mousePosition)
{
	sf::Vector2i previusPosition = position;
	position = mousePosition;
	circle.setPosition(sf::Vector2f(position));
	indexText.SetPosition(position);

	if (extraText.has_value())
		extraText->SetPosition(position + sf::Vector2i(0.f, -circle.getRadius() * 1.2f));

	std::erase_if(edges, [](auto& e) {return e.expired(); });

	for (auto& e : edges)
	{
		auto temp = e.lock();
		if (temp->GetPosition() == previusPosition)
		{
			temp->Update(position, temp->GetEndPosition(), true);
		}
		else
		{
			temp->Update(temp->GetPosition(), position);
		}
	}
}

void NodeCircle::InsertEdge(std::weak_ptr<EdgeShape> edge)
{
	edges.push_back(edge);
}

void NodeCircle::AddText(std::string text)
{
	extraText.emplace(text, (sf::Vector2f)position + sf::Vector2f(0.f, -circle.getRadius() * 1.2f), 30, sf::Color::Green);
}

std::vector<std::shared_ptr<EdgeShape>> NodeCircle::GetLinkedEdges()
{
	std::vector<std::shared_ptr<EdgeShape>> temp;
	for (auto& e : edges)
	{
		if (!e.expired())
		{
			temp.push_back(e.lock());
		}
	}
	return temp;
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

