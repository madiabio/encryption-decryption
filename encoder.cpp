#include "pch.h"
#include "Encoder.h"
#include <random>
#include <ctime>
#include <string>

char Encoder::getRandomLetter()
{
	// Seed the random number generator with the current time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Generate a random number between 0 and 25
	int randomNumber = std::rand() % 26;

	// Convert the random number to a capital letter (A=65, B=66, etc.)
	char randomLetter = static_cast<char>('A' + randomNumber);

	return randomLetter;

}