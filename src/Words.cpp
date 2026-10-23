#include <cstddef>
#include <fstream>
#include <iterator>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "Words.h"

namespace
{
	constexpr const char* WORD_LIST_PATH = "assets/data/wordList.txt";
}

Words::Words()
{
	ReadFile(WORD_LIST_PATH);
}

void Words::ReadFile(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
		throw std::runtime_error(path + " was not found.");

	std::string str;
	while (std::getline(file, str))
	{
		if (!str.empty() && str.back() == '\r')
			str.pop_back();
		if (!str.empty())
			set.insert(str);
	}

	if (set.empty())
		throw std::runtime_error(path + " contains no words.");
}

const std::string& Words::RandomTarget() const
{
	static std::mt19937 gen{ std::random_device{}() };

	std::uniform_int_distribution<std::size_t> dist(0, set.size() - 1);
	const std::size_t randomIndex = dist(gen);

	auto it = set.begin();
	std::advance(it, randomIndex);

	return *it;
}
