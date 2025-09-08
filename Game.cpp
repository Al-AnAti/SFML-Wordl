#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>

#include "Game.h"
#include "SFML/Graphics.hpp"
#include "Words.h"
#include "Square.h"

unsigned int WIDTH  = 1280;
unsigned int HEIGHT = 720;

Game::Game()
{
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Wordle");
	init();
}

Game::~Game()
{
	for (auto& row : sqs)
		for (auto& sq : row)
			delete sq;
}

void Game::init()
{
	finished = false;
	wordNo = 0;
	chNo = 0;

	target = words.RandomTarget();
	guesses.clear();

	float hGap = 15.f;
	float vGap = 20.f;
	float xPointStart = 435;
	float yPoint = 50;

	sqs.resize(6); // 6 rows
	for (int r = 0; r < 6; r++)
	{
		sqs[r].resize(5); // 5 columns
		float xPoint = xPointStart;

		for (int c = 0; c < 5; c++)
		{
			sqs[r][c] = new Square{ { xPoint, yPoint } };
			xPoint += Square::WIDTH + hGap;
		}
		yPoint += Square::HEIGHT + vGap;
	}
}

void Game::Run()
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::R && finished)
				{
					init();
				}
			}	

			if(!finished)
				Input(event);
		}
		Render();
	}
}

void Game::Render()
{
	window.clear(sf::Color(40, 70, 120));

	for (auto& row : sqs)
	{
		for (auto& sq : row)
		{
			window.draw(sq->shape);
			window.draw(sq->ch);
		}
	}
	
	if (finished)
		window.draw(endText);

	window.display();
}

void Game::Input(const sf::Event& event)
{
	static std::string input;

	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode >= 32 && event.text.unicode < 128) // printable ASCII chars only
		{
			char c = toupper(static_cast<char>(event.text.unicode));
			if(chNo < 5 && isalpha(c))
			{
				input += c;
				sqs[wordNo][chNo]->setCh(c);
				chNo++;
			}
		}
	}

	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			if (chNo == 5 && words.set.count(input) && !guesses.count(input))
			{
				guesses.insert(input);

				Color(wordNo, Check(input));
				wordNo++;
				chNo = 0;

				if (input == target)
					End(1);
				else if (wordNo == 6)
					End(0);

				input.clear();
			}
		}
		else if (event.key.code == sf::Keyboard::BackSpace)
		{
			if (chNo > 0)
			{
				chNo--;
				sqs[wordNo][chNo]->setCh(' ');
				input.pop_back();
			}
		}

	}
}

std::vector<int> Game::Check(const std::string& guess)
{
	std::unordered_set<char> target_chars(target.begin(), target.end());
	
	std::vector<int> colors(5);
	// 1  = Green
	// 0  = Yellow
	// -1 = Gray

	for (int i = 0; i < 5; i++)
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

void Game::Color(int wordNo, std::vector<int> colors)
{
	for (int i = 0; i < 5; i++)
		sqs[wordNo][i]->setColor(colors[i]);
}

void Game::End(int state)
{
	std::cout << target << std::endl;

	finished = true;
	endText.setFont(sqs[0][0]->font);
	endText.setPosition(sf::Vector2f(560, 620));
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