#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>

#include "SFML\Graphics.hpp"
#include "Words.h"
#include "Square.h"

class Game
{
private:
	sf::RenderWindow window; // the window of the game.
	sf::Event event; // Event handeler.
	std::vector <std::vector<Square*>> sqs; // 2d array for the squares.
	
	Words words; // words obj to get all the words and the target.
	std::unordered_set<std::string> guesses; // set to store all the guesses.
	std::string target; // the target word.

	sf::Text endText; // You lost!, You won! text.

	bool finished; // bool to know if the game is done.
	int wordNo; // the number of the current guess.
	int chNo; // th number of the square that the player writing on.

	void init(); // to create the window and the squares.
	void Render(); // to draw everything on the scene.
	void Input(const sf::Event& event); // to take the use inputs.
	std::vector<int> Check(const std::string& guess); // compare the guess with the target.
	void Color(int wordNo, std::vector<int> result); //  Change the color of the squares based on the Check results.
	void End(int state); // displays the text at the end of the game, 1 = win, 0 = lose.


public:
	Game(); // Constructor.
	~Game(); // Destructor.
	void Run(); // main loop + all function calls.
};