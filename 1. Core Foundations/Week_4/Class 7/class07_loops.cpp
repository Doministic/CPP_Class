
#include <iostream>

int main()
{
	// Loops continue until a condition is met
	// There are three types of loops in C++: for, while, and do-while
	
	// For Loop
	/*
	for (int i = 0; i < 20; i += 5)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << "j = " << j << std::endl;
			if (i == 5)
			{
				break;
			}
		}
		std::cout << "i = " << i << std::endl;
		if (i == 5)
		{
			break;
		}
	}
	*/

	// While Loop
	int guess = 60;
	int playerGuess = 0;
	/*
	while (true)
	{
		std::cout << "Hello World";
		std::cout << " count = " << count << std::endl;
		count += 3;
		if (count < 5)
		{
			continue;
		}
		std::cout << "count is now 5 or more" << std::endl;
		if (count >= 10)
		{
			break;
		}
	}
	*/

	// Do-While Loop
	do {
		std::cout << "Hello to the hardest game ever! \n";
		std::cout << "Guess a number between 1 and 100: \n";
		std::cin >> playerGuess;
		if (playerGuess < guess) {
			std::cout << "Your guess is too low! Try again. \n";
		}
		else if (playerGuess > guess) {
			std::cout << "Your guess is too high! Try again. \n";
		}
		else {
			std::cout << "Congratulations! You guessed the number! \n";
		}
	} while (playerGuess != guess);

	return 0;
}