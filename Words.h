#pragma once

#include <unordered_set>
#include <string>
#include <fstream>

class Words
{
private:
	std::ifstream file; // the .txt file we're reading the words from

public: 
	std::unordered_set<std::string> set; // saving all the words temperorly for the game
	std::string target; // the target the player is trying to find

	Words(); // Constructor.
	void ReadFile(); // method to read the .txt file and save all the words in the set.
	const std::string& RandomTarget() const; // methods to choose a random target from the set.
};
