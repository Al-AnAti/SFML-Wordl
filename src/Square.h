#pragma once

#include <SFML/Graphics.hpp>

struct Square
{
	sf::RectangleShape shape; // the square that is displayed in the scene.
	sf::Text ch; // the character that is displayed in the square.

	static const float WIDTH;
	static const float HEIGHT;

	Square(const sf::Vector2f& pos, const sf::Font& font); // Constructor. The font must outlive the square.
	sf::Vector2f findChPos(); // finds the position of the character inside the square.
	void setCh(char c); // change the character that is displayed.
	void setColor(int color); // change the color of the square.
};
