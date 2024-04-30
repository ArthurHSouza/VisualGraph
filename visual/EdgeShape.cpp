#include "EdgeShape.hpp"
#include <numbers>
#include <cmath>
#include <iostream>

EdgeShape::EdgeShape(std::size_t begningIndex, std::size_t endIndex, sf::Vector2i begining, sf::Vector2i end) :
	SelectableVisualObject(begining, 10.f, sf::Color::Black, ColorPallet::celestBlue, ColorPallet::carminRed),
	begningIndex{begningIndex}, endIndex{endIndex}, endPosition{end}, weightText(std::to_string(weight).substr(0,5))
{
	weightText.SetColor(ColorPallet::petrolBlue);

	collisionPoint.setSize(sf::Vector2f(20.f,20.f));
	collisionPoint.setOrigin(collisionPoint.getGlobalBounds().getSize() / 2.f);
	collisionPoint.setFillColor(deleteColor);

	int diffy = position.y - end.y;
	float dist = sqrtf(std::pow(position.x - end.x, 2) + std::pow(diffy, 2));

	arrowRect.setSize(sf::Vector2f(size,dist));
	arrowRect.setOrigin(
		arrowRect.getGlobalBounds().getSize().x/2.f, 
		arrowRect.getGlobalBounds().getSize().y
	);
	arrowRect.setPosition(sf::Vector2f(begining));
	arrowRect.setFillColor(defaultColor);

	float rotationDegrees = asinf(diffy / dist) * 180.f / std::numbers::pi_v<float>;

	// First quadrant or Fourth quadrant
	if ((endPosition.x >= position.x && endPosition.y <= position.y) || (endPosition.x >= position.x && endPosition.y >= position.y))
	{
		rotationDegrees = 90 - rotationDegrees;
	}
	//Second quadrant or Third quadrant
	else if ((endPosition.x <= position.x && endPosition.y <= position.y) || (endPosition.x <= position.x && endPosition.y >= position.y))
	{
		rotationDegrees -= 90;
	}
	
	arrowRect.setRotation(rotationDegrees);

	float targetX = std::lerp(position.x, endPosition.x, 0.5f);
	float targetY = std::lerp(position.y, endPosition.y, 0.5f);
	collisionPoint.setPosition(targetX, targetY);

	arrowHead.setPointCount(3);
	arrowHead.setFillColor(defaultColor);
	UpdateArrowHead(diffy, dist);
	UpdateWeightText();

}

void EdgeShape::UpdateArrowHead(const int& diffY, const float& distance)
{
	float rotationRadians = asinf(diffY / distance);
	sf::Vector2f offset1ArrowHead;
	sf::Vector2f offset2ArrowHead;
	sf::Vector2f offset3ArrowHead;
	const float distanceOtherPoints = 75.f;
	const float offsetAngle = std::numbers::pi_v<float> / 10.f;
	const float nodeRadius = 50.f;
	//First quadrant
	if (endPosition.x >= position.x && endPosition.y <= position.y)
	{
		offset1ArrowHead = sf::Vector2f(
			-nodeRadius * cosf(rotationRadians),
			nodeRadius * sinf(rotationRadians)
		);

		offset2ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians + offsetAngle),
			distanceOtherPoints * sinf(rotationRadians + offsetAngle)
		);

		offset3ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians - offsetAngle),
			distanceOtherPoints * sinf(rotationRadians - offsetAngle)
		);
	}

	else if (endPosition.x <= position.x && endPosition.y <= position.y)
	{
		//Adjusting the angle, rotationRadians at the moment is like the angle was started at pi
		//so we make this subtraction so we can get the angle started from 0
		rotationRadians = std::numbers::pi_v<float> - rotationRadians;
		offset1ArrowHead = sf::Vector2f(
			-nodeRadius * cosf(rotationRadians),
			nodeRadius * sinf(rotationRadians)
		);

		offset2ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians + offsetAngle),
			distanceOtherPoints * sinf(rotationRadians + offsetAngle)
		);

		offset3ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians - offsetAngle),
			distanceOtherPoints * sinf(rotationRadians - offsetAngle)
		);
	}
	
	else if (endPosition.x <= position.x && endPosition.y >= position.y)
	{
		//Adjusting the angle, rotationRadians at the moment is like the angle was started at pi and going clockwise
		//so is a negative value, we make this sum so we can get the angle started from 0 counter-clockwise
		rotationRadians = std::numbers::pi_v<float> +fabs(rotationRadians);
		offset1ArrowHead = sf::Vector2f(
			-nodeRadius * cosf(rotationRadians),
			nodeRadius * sinf(rotationRadians)
		);

		offset2ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians + offsetAngle),
			distanceOtherPoints * sinf(rotationRadians + offsetAngle)
		);

		offset3ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians - offsetAngle),
			distanceOtherPoints * sinf(rotationRadians - offsetAngle)
		);
	}
	else if (endPosition.x >= position.x && endPosition.y >= position.y)
	{
		//Adjusting the angle, rotationRadians at the moment is like the angle was started at 0 and going clockwise
		//so is a negative value, we make this subtraction so we can get the angle started from 0 and going counter-clockwise
		rotationRadians = 2.f * std::numbers::pi_v<float>+rotationRadians;
		offset1ArrowHead = sf::Vector2f(
			-nodeRadius * cosf(rotationRadians),
			nodeRadius * sinf(rotationRadians)
		);

		offset2ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians + offsetAngle),
			distanceOtherPoints * sinf(rotationRadians + offsetAngle)
		);

		offset3ArrowHead = sf::Vector2f(
			-distanceOtherPoints * cosf(rotationRadians - offsetAngle),
			distanceOtherPoints * sinf(rotationRadians - offsetAngle)
		);
	}

	arrowHead.setPoint(0, (sf::Vector2f)endPosition + offset1ArrowHead);
	arrowHead.setPoint(1, (sf::Vector2f)endPosition + offset2ArrowHead);
	arrowHead.setPoint(2, (sf::Vector2f)endPosition + offset3ArrowHead);
}

void EdgeShape::UpdateWeightText()
{
	const float offsetAngle = std::numbers::pi_v<float> / 20.f;

	int diffY = (position.y - collisionPoint.getPosition().y);
	float dist = std::sqrtf(std::pow<int>(position.x - collisionPoint.getPosition().x, 2) + std::pow<int>(diffY, 2));
	float textAngle = asinf(diffY / dist);

	sf::Vector2f textPosition;
	float textRotation = asinf(diffY / dist) * 180.f / std::numbers::pi_v<float>;

	//First quadrant
	if (endPosition.x >= position.x && endPosition.y <= position.y)
	{
		//Adjusting the angle
		textAngle -= offsetAngle;
		textPosition = sf::Vector2f(
			-dist * cosf(textAngle),
			dist * sinf(textAngle)
		);
		textRotation = 360.f - textRotation;
	}
	//Second quadrant 
	else if (endPosition.x <= position.x && endPosition.y <= position.y)
	{
		//Adjusting the angle, textAngle at the moment is like the angle was started at pi
		//so we make this subtraction so we can get the angle started from 0
		textAngle = std::numbers::pi_v<float> - textAngle + offsetAngle;
		textPosition = sf::Vector2f(
			-dist * cosf(textAngle),
			dist * sinf(textAngle)
		);
	}
	//Third quadrant
	else if (endPosition.x <= position.x && endPosition.y >= position.y)
	{
		//Adjusting the angle, textAngle at the moment is like the angle was started at pi and going clockwise
		//so is a negative value, we make this sum so we can get the angle started from 0 counter-clockwise
		textAngle = std::numbers::pi_v<float> +fabs(textAngle) + offsetAngle;
		textPosition = sf::Vector2f(
			-dist * cosf(textAngle),
			dist * sinf(textAngle)
		);
	}
	//Fourth quadrant
	else if (endPosition.x >= position.x && endPosition.y >= position.y)
	{
		//Adjusting the angle, textAngle at the moment is like the angle was started at 0 and going clockwise
		//so is a negative value, we make this subtraction so we can get the angle started from 0 and going counter-clockwise
		textAngle =  2.f * std::numbers::pi_v<float>+textAngle - offsetAngle;
		textPosition = sf::Vector2f(
			-dist * cosf(textAngle),
			dist * sinf(textAngle)
		);
		textRotation = 360 - textRotation;
	}
	
	weightText.SetPosition( endPosition + (sf::Vector2i)textPosition);
	weightText.SetRotation(textRotation);
}

void EdgeShape::Draw(sf::RenderTarget& window) const
{
	window.draw(arrowRect);
	if(drawCollisionPoint)
		window.draw(collisionPoint);
	window.draw(arrowHead);
	weightText.Draw(window);
}

void EdgeShape::Update(sf::Vector2i begining, sf::Vector2i end, bool shallChangePosition)
{
	position = begining;
	endPosition = end;
	if (shallChangePosition)
	{
		arrowRect.setPosition(sf::Vector2f(begining));
	}
	int diffy = position.y - end.y ;
	float dist = sqrtf(std::pow(position.x - end.x, 2) + std::pow(diffy, 2));
	
	arrowRect.setScale(1, dist / arrowRect.getSize().y);

	float rotationDegrees = asinf(diffy / dist) * 180.f / std::numbers::pi_v<float>;

	// First quadrant or Fourth quadrant
	if ((endPosition.x >= position.x && endPosition.y <= position.y) || (endPosition.x >= position.x && endPosition.y >= position.y))
	{
		rotationDegrees = 90 - rotationDegrees;
	}
	//Second quadrant or Third quadrant
	else if ((endPosition.x <= position.x && endPosition.y <= position.y) || (endPosition.x <= position.x && endPosition.y >= position.y))
	{
		rotationDegrees -= 90;
	}

	arrowRect.setRotation(rotationDegrees);

	float targetX = std::lerp(position.x, endPosition.x, 0.5f);
	float targetY = std::lerp(position.y, endPosition.y, 0.5f);
	collisionPoint.setPosition(targetX, targetY);

	UpdateArrowHead(diffy, dist);
	UpdateWeightText();
}

void EdgeShape::FillWithDefinedColor(DefinedColor color)
{
	drawCollisionPoint = false;
	switch (color)
	{
	case SelectableVisualObject::DefinedColor::DefaultColor:
		arrowRect.setFillColor(defaultColor);
		arrowHead.setFillColor(defaultColor);
		break;
	case SelectableVisualObject::DefinedColor::SelectedColor:
		arrowRect.setFillColor(selectedColor);
		arrowHead.setFillColor(selectedColor);
		break;
	case SelectableVisualObject::DefinedColor::DeleteColor:
		drawCollisionPoint = true;
		arrowRect.setFillColor(deleteColor);
		arrowHead.setFillColor(deleteColor);
		break;
	default:
		break;
	}
}

const sf::Vector2i EdgeShape::GetPosition() const
{
	return position;
}

const sf::Vector2i EdgeShape::GetEndPosition() const
{
	return endPosition;
}

const std::size_t EdgeShape::GetBeginingIndex() const
{
	return begningIndex;
}

const std::size_t EdgeShape::GetEndIndex() const
{
	return endIndex;
}

const float EdgeShape::GetWeight() const
{
	return weight;
}

bool EdgeShape::Select(sf::Vector2i& mousePos)
{
	sf::Rect<float> mouseRec(sf::Vector2f(mousePos), sf::Vector2f(1, 1));
	return collisionPoint.getGlobalBounds().intersects(mouseRec);
}
