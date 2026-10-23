#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Square.h"
#include "Words.h"

namespace
{
	constexpr unsigned int WIDTH  = 1280;
	constexpr unsigned int HEIGHT = 720;
	constexpr int ROWS = 6;
	constexpr int COLS = 5;
	constexpr const char* FONT_PATH = "assets/fonts/arial.ttf";
}

Game::Game()
{
	if (!font.loadFromFile(FONT_PATH))
		throw std::runtime_error(std::string("could not load ") + FONT_PATH);

	window.create(sf::VideoMode(WIDTH, HEIGHT), "Wordle");
	init();
}

void Game::init()
{
	finished = false;
	wordNo = 0;
	chNo = 0;
	input.clear();

	target = words.RandomTarget();
	guesses.clear();

	const float hGap = 15.f;
	const float vGap = 20.f;
	const float xPointStart = 435.f;
	float yPoint = 50.f;

	sqs.clear();
	sqs.reserve(ROWS);
	for (int r = 0; r < ROWS; r++)
	{
		std::vector<Square> row;
		row.reserve(COLS);
		float xPoint = xPointStart;

		for (int c = 0; c < COLS; c++)
		{
			row.emplace_back(sf::Vector2f{ xPoint, yPoint }, font);
			xPoint += Square::WIDTH + hGap;
		}
		sqs.push_back(std::move(row));
		yPoint += Square::HEIGHT + vGap;
	}
}

void Game::Run()
{
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				else if (event.key.code == sf::Keyboard::R && finished)
					init();
			}

			if (!finished)
				Input(event);
		}
		Render();
	}
}

void Game::Render()
{
	window.clear(sf::Color(40, 70, 120));

	for (const auto& row : sqs)
	{
		for (const auto& sq : row)
		{
			window.draw(sq.shape);
			window.draw(sq.ch);
		}
	}

	if (finished)
		window.draw(endText);

	window.display();
}

void Game::Input(const sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode >= 32 && event.text.unicode < 128) // printable ASCII chars only
		{
			const char c = static_cast<char>(std::toupper(static_cast<int>(event.text.unicode)));
			if (chNo < COLS && std::isalpha(static_cast<unsigned char>(c)))
			{
				input += c;
				sqs[wordNo][chNo].setCh(c);
				chNo++;
			}
		}
	}

	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			if (chNo == COLS && words.IsAllowed(input) && !guesses.count(input))
			{
				guesses.insert(input);

				Color(wordNo, Check(input));
				wordNo++;
				chNo = 0;

				if (input == target)
					End(1);
				else if (wordNo == ROWS)
					End(0);

				input.clear();
			}
		}
		else if (event.key.code == sf::Keyboard::BackSpace)
		{
			if (chNo > 0)
			{
				chNo--;
				sqs[wordNo][chNo].setCh(' ');
				input.pop_back();
			}
		}
	}
}

std::vector<int> Game::Check(const std::string& guess) const
{
	std::unordered_set<char> target_chars(target.begin(), target.end());

	std::vector<int> colors(COLS);
	// 1  = Green
	// 0  = Yellow
	// -1 = Gray

	for (int i = 0; i < COLS; i++)
	{
		if (target_chars.count(guess[i]))
		{
			if (guess[i] == target[i])
				colors[i] = 1; // Green
			else
				colors[i] = 0; // Yellow
		}
		else
			colors[i] = -1; // Gray
	}

	return colors;
}

void Game::Color(int row, const std::vector<int>& colors)
{
	for (int i = 0; i < COLS; i++)
		sqs[row][i].setColor(colors[i]);
}

void Game::End(int state)
{
	std::cout << target << std::endl;

	finished = true;
	endText.setFont(font);
	endText.setPosition(sf::Vector2f(560.f, 620.f));
	endText.setCharacterSize(30);

	if (state == 1) // player won
	{
		endText.setString("You Won!!!");
		endText.setFillColor(sf::Color::Green);
	}
	else if (state == 0) // player lost
	{
		endText.setString("You Lost!!");
		endText.setFillColor(sf::Color::Red);
	}
}
