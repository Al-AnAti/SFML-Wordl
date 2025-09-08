#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <iterator>

#include "words.h"

Words::Words()
{
	file.open("wordList.txt");
	
	if (!file.is_open())
	{
		std::cerr << "wordList.txt was not found." << std::endl;
		exit(1);
	}

	ReadFile();
}

void Words::ReadFile()
{
	std::string str;

	while (std::getline(file, str))
	{
		set.insert(str);
	}

	file.close();

	//std::cout << "isOpen = " << file.is_open() << std::endl;
	//std::cout << "setSize = " << set.size() << std::endl;
	//std::cout << "wordSize = " << set.begin()->size() << std::endl;
}

const std::string& Words::RandomTarget() const
{
	if (set.empty())
		throw std::runtime_error("word set is empty");

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dist(0, Words::set.size() - 1);
	int randomIndex = dist(gen);

	auto it = set.begin();
	std::advance(it, randomIndex);
	 
	return *it;
}