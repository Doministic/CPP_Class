// Function Overloading and Scope Resolution
// Covering the topic of scope resolution and using the same name for different functions
/*
#include <iostream>
#include <chrono>

int main()
{
	std::string name = "dominic";
	const char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	/*
	int x = 100;
	int y = 0;
	
	auto startWhile = std::chrono::high_resolution_clock::now();
	while (y < x)
	{
		for (int i = 0; i < name.size(); i++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			if (name[i] == letters[18])
			{
				auto stop = std::chrono::high_resolution_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

				std::cout << "S: " << duration.count() << "\n";
			}
			else if (name[i] == letters[0])
			{
				auto stop = std::chrono::high_resolution_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

				std::cout << "A: " << duration.count() << "\n";
			}
			else if (name[i] == letters[1])
			{
				auto stop = std::chrono::high_resolution_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

				std::cout << "B: " << duration.count() << "\n";
			}
			else if (name[i] == letters[8])
			{
				auto stop = std::chrono::high_resolution_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

				std::cout << "I: " << duration.count() << "\n";
			}
		}
		y++;
	}
	auto stopWhile = std::chrono::high_resolution_clock::now();
	auto durationWhile = std::chrono::duration_cast<std::chrono::microseconds>(stopWhile - startWhile);

	std::cout << "While Loop: " << durationWhile.count() << "\n";
	
	auto startNest = std::chrono::high_resolution_clock::now();
	for (int j = 0; j < name.size(); j++)
	{
		for (int k = 0; k < 26; k++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			if (name[j] == letters[k])
			{
				auto stop = std::chrono::high_resolution_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

				std::cout << "Name: " << duration.count() << "\n";
			}
		}
	}
	auto stopNest = std::chrono::high_resolution_clock::now();

	auto durationNest = std::chrono::duration_cast<std::chrono::microseconds>(stopNest - startNest);

	std::cout << "Nested ForLoop: " << durationNest.count() << "\n";

	std::cout << "\nFinished.";

	return 0;
}
*/