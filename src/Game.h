#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Square.h"
#include "Words.h"

class Game
{
private:
	sf::RenderWindow window; // the window of the game.
	sf::Font font; // the one font shared by every square and the end text.
	std::vector<std::vector<Square>> sqs; // 6 rows x 5 columns of squares.

	Words words; // words obj to get all the words and the target.
	std::unordered_set<std::string> guesses; // set to store all the guesses.
	std::string target; // the target word.
	std::string input; // the guess currently being typed.

	sf::Text endText; // You lost!, You won! text.

	bool finished = false; // bool to know if the game is done.
	int wordNo = 0; // the number of the current guess.
	int chNo = 0; // the number of the square that the player is writing on.

	void init(); // to create the squares and pick a new target.
	void Render(); // to draw everything on the scene.
	void Input(const sf::Event& event); // to take the user inputs.
	std::vector<int> Check(const std::string& guess) const; // compare the guess with the target.
	void Color(int row, const std::vector<int>& colors); // change the color of the squares based on the Check results.
	void End(int state); // displays the text at the end of the game, 1 = win, 0 = lose.

public:
	Game(); // Constructor.
	void Run(); // main loop + all function calls.
};
