#include <string>

#include <SFML/Graphics.hpp>

#include "Square.h"

const float Square::WIDTH  = 70.f;
const float Square::HEIGHT = 70.f;

Square::Square(const sf::Vector2f& pos, const sf::Font& font)
{
	shape.setPosition(pos);
	shape.setSize({ WIDTH, HEIGHT });
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(5);
	shape.setOutlineColor(sf::Color::Black);

	ch.setFont(font);
	ch.setString(" ");
	ch.setCharacterSize(28);
	ch.setPosition(findChPos());
	ch.setFillColor(sf::Color::Black);
}

sf::Vector2f Square::findChPos()
{
	sf::FloatRect textBounds = ch.getLocalBounds();
	ch.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);

	sf::Vector2f rectPos = shape.getPosition();
	sf::Vector2f rectSize = shape.getSize();

	return { rectPos.x + rectSize.x / 2.f, rectPos.y + rectSize.y / 2.f };
}

void Square::setCh(char c)
{
	ch.setString(std::string(1, c));
	ch.setPosition(findChPos());
}

void Square::setColor(int color)
{
	// 1  = Green
	// 0  = Yellow
	// -1 = Gray

	switch (color)
	{
	case 1 : shape.setFillColor(sf::Color::Green);
		break;
	case 0 : shape.setFillColor(sf::Color::Yellow);
		break;
	case -1: shape.setFillColor(sf::Color(50, 50, 50));
		break;
	default:
		break;
	}
}
