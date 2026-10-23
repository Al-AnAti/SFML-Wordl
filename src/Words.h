#pragma once

#include <string>
#include <unordered_set>
#include <vector>

class Words
{
private:
	std::vector<std::string> answers; // words the game can pick as the target.
	std::unordered_set<std::string> allowed; // every word accepted as a guess (answers included).

	static std::vector<std::string> ReadFile(const std::string& path); // read one word per line, throws if the file is missing or empty.

public:
	Words(); // Constructor. Throws std::runtime_error if a word list can't be read.
	bool IsAllowed(const std::string& guess) const; // true if the guess is in either list.
	const std::string& RandomTarget() const; // choose a random target from the answers.
};
