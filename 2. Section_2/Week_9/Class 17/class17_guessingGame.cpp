// The Guessing Game in C++
// This is the first version of the guessing game using everything we have learned so far. 

#include <iostream>
#include <random>

enum difficulty
{
	Easy = 0,
	Normal = 1,
	Hard = 2, 
	Expert = 3, 
	Master = 4
};

// forward declaration:
static difficulty setDifficultyFromUserInput(int& userInput);

std::random_device rd;  // Obtain a random number from hardware
std::mt19937 gen(rd()); // Seed the generator

static void printMainMenu()
{
	std::cout << "-----MAIN MENU-----\n";
	std::cout << "1. Start Game\n";
	std::cout << "2. Set Difficulty\n";
	std::cout << "3. Exit\n";
}

static int getRandomNumberInRange(signed int& min, signed int& max)
{
	std::uniform_int_distribution<> dist(min, max); // Define the range
	return dist(gen);
}

static std::pair<std::pair<int, int>, std::pair<int, int>> setDifficulty(difficulty level)
{
	signed int min = 1, max = 100;
	unsigned int attempts = 5;

	switch (level)
	{
	case Easy:
		min = 1;
		max = 100;
		attempts = 10;
		break;
	case Normal:
		min = 1;
		max = 100;
		attempts = 5;
		break;
	case Hard:
		min = 1;
		max = 5000;
		attempts = 15;
		break;
	case Expert:
		min = -1000;
		max = 10000;
		attempts = 30;
		break;
	case Master:
		min = -10000;
		max = 100000;
		attempts = 30;
		break;
	default:
		min = 1;
		max = 100;
		attempts = 10;
		break;
	}
	signed int randomNumber = getRandomNumberInRange(min, max);
	return { {min, max}, { randomNumber, attempts } };
}

static int printDifficulty(difficulty diffLevel)
{
	switch (diffLevel)
	{
	case Easy:
		std::cout << "You have selected Easy difficulty.\n";
		break;
	case Normal:
		std::cout << "You have selected Normal difficulty.\n";
		break;
	case Hard:
		std::cout << "You have selected Hard difficulty.\n";
		break;
	case Expert:
		std::cout << "You have selected Expert difficulty.\n";
		break;
	case Master:
		std::cout << "You have selected Master difficulty.\n";
		break;
	default:
		std::cout << "Invalid difficulty level.\n";
		return -1;
	}
	return 0;
}

static difficulty setDifficultyFromUserInput(int& userInput)
{
	std::cout << "User Input: " << userInput << "\n";
	difficulty level = static_cast<difficulty>(userInput);
	if (userInput < 0 || userInput > 4)
	{
		std::cout << "Invalid input. Defaulting to Normal.\n";
		level = Normal;
	}
	else
	{
		level = static_cast<difficulty>(userInput);
		printDifficulty(level);
	}

	return level;
}

static void printDifficultyOptions()
{
	std::cout << "Please select a difficulty level (0-4): ";
	std::cout << "Difficulty Levels:\n";
	std::cout << "-----------------------------------------------------------------------------------\n";
	std::cout << " To select a difficulty enter the number corresponding to the difficulty level.\n";
	std::cout << "-----------------------------------------------------------------------------------\n";
	std::cout << "0. Easy: Min set to 1 - Max set to 100 - Number of attempts set to 10\n";
	std::cout << "1. Normal: min set to 1 - Max set to 100 - Number of attempts set to 5\n";
	std::cout << "2. Hard: Min set to 1 - Max set to 5000 - Number of attempts set to 15\n";
	std::cout << "3. Expert: Min set to -1000 - Max set to 10000 - Number of attempts set to 30\n";
	std::cout << "4. Master: Min set to -10000 - Max set to 100000 - Number of attempts set to 50\n";
}

static int& getUserInput(int& userInput)
{
	std::cout << "Please enter your choice: ";
	std::cin >> userInput;
	return userInput;
}

static int playAgain(char *playAgain)
{
	if (*playAgain == 'y')
	{
		std::cout << "Great! Let's play again!\n";
		return 1;
	}
	else
	{
		std::cout << "Thank you for playing! Goodbye!\n";
		return 0;
	}
}

int main()
{
	int playing = 1;
	char play = 'y';
	int numberToGuess;
	difficulty level = Normal;
	std::pair<std::pair<int, int>, std::pair<int, int>> difficultyLevel = setDifficulty(Normal); // Default difficulty level
	int userMainMenuInput;
	while (playing == 1)
	{
		std::cout << "Welcome to the Guessing Game!\n";
		printMainMenu();

		getUserInput(userMainMenuInput);

		if (userMainMenuInput == 1)
		{
			std::cout << "Starting the game...\n";
		}
		else if (userMainMenuInput == 2)
		{
			printDifficultyOptions();
			int userLevelInput;
			getUserInput(userLevelInput);
			level = setDifficultyFromUserInput(userLevelInput);
			difficultyLevel = setDifficulty(level);
		}
		else if (userMainMenuInput == 3)
		{
			std::cout << "Exiting the game. Goodbye!\n";
			return 0;
		}
		else
		{
			std::cout << "Invalid option. Please try again.\n";
			return -1;
		}

		numberToGuess = setDifficulty(level).second.first;
		int attempts = setDifficulty(level).second.second;

		std::cout << "The number to guess is set. You have " << attempts << " attempts to guess it.\n";

		int userGuess;
		while (attempts > 0)
		{
			std::cout << "You have " << attempts << " attempts left. Please enter your guess: ";
			std::cin >> userGuess;
			if (userGuess < numberToGuess)
			{
				std::cout << "Your guess is too low. Try again. \n";
			}
			else if (userGuess > numberToGuess)
			{
				std::cout << "Your guess is too high. Try again. \n";
			}
			attempts--;
			if (userGuess == numberToGuess)
			{
				std::cout << "Congrats you guess the number: " << numberToGuess << "!\n";
				std::cout << "You win the game!\n";
				std::cout << "Would you like to play again? ('y' or 'n'): ";
				std::cin >> play;
				playing = playAgain(&play);
				break;
			} else if (attempts == 0)
			{
				std::cout << "You have run out of attempts. The number was: " << numberToGuess << ".\n";
				std::cout << "Better luck next time!\n";
				std::cout << "Would you like to play again? ('y' or 'n'): ";
				std::cin >> play;
				playing = playAgain(&play);
			}
		}
	}
	return 0;
}
