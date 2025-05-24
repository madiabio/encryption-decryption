#pragma once
#include <string>

class Menu
{
private:
	std::string str;
	int gridSize;
	int totalRounds;
public:
	Menu() : str(""), gridSize(0), totalRounds(0) {}
};