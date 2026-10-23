#pragma once

#include <string>
#include <unordered_set>

class Words
{
public:
	std::unordered_set<std::string> set; // all the accepted words.

	Words(); // Constructor. Throws std::runtime_error if the word list can't be read.
	void ReadFile(const std::string& path); // read the .txt file and save all the words in the set.
	const std::string& RandomTarget() const; // choose a random target from the set.
};
