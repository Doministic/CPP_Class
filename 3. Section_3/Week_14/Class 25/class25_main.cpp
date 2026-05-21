
// Ctl C - Ctl V
#include "header.h"
/*
int main()
{	
	
	const int N = 26;
									// 0    1    2    3    4
	char EnglishAlphabet_lower[N] = {'a', 'b', 'c', 'd', 'e'};
	char EnglishAlphabet_upper[10000] = { 'A', 'B', 'C', 'D', 'E' };

	std::cout << "Space Complexity: " << sizeof(EnglishAlphabet_lower) << " Bytes * " << sizeof(char) << " Char in Bytes \n";
	std::cout << "Space Complexity: " << sizeof(EnglishAlphabet_upper) << " Bytes * " << sizeof(char) << " Char in Bytes \n";

	auto startOne = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++)
	{
		if (EnglishAlphabet_lower[i] == 'a')
		{
			break;
		}
	}
	auto stopOne = std::chrono::high_resolution_clock::now();

	auto durationOne = std::chrono::duration_cast<std::chrono::nanoseconds>(stopOne - startOne);

	std::cout << "Time Complexity: " << durationOne.count() << " NanoSeconds\n";


	auto startTwo = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 10000; i++)
	{
		if (EnglishAlphabet_lower[i] == 'f')
		{
			break;
		}
	}

	auto stopTwo = std::chrono::high_resolution_clock::now();

	auto durationTwo = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTwo - startTwo);

	std::cout << "Time Complexity: " << durationTwo.count() << " Nanoseconds\n";


	return 0;
}*/