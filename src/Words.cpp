#include <cstddef>
#include <fstream>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

#include "Words.h"

namespace
{
	constexpr const char* ANSWERS_PATH = "assets/data/answers.txt";
	constexpr const char* ALLOWED_PATH = "assets/data/allowed.txt";
}

Words::Words()
{
	answers = ReadFile(ANSWERS_PATH);

	// Every answer is also a valid guess, so the allowed set is both lists together.
	allowed.insert(answers.begin(), answers.end());
	for (const std::string& word : ReadFile(ALLOWED_PATH))
		allowed.insert(word);
}

std::vector<std::string> Words::ReadFile(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
		throw std::runtime_error(path + " was not found.");

	std::vector<std::string> words;
	std::string str;
	while (std::getline(file, str))
	{
		if (!str.empty() && str.back() == '\r')
			str.pop_back();
		if (!str.empty())
			words.push_back(str);
	}

	if (words.empty())
		throw std::runtime_error(path + " contains no words.");

	return words;
}

bool Words::IsAllowed(const std::string& guess) const
{
	return allowed.count(guess) > 0;
}

const std::string& Words::RandomTarget() const
{
	static std::mt19937 gen{ std::random_device{}() };

	std::uniform_int_distribution<std::size_t> dist(0, answers.size() - 1);
	return answers[dist(gen)];
}
