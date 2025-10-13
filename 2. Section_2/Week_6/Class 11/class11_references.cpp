// References
// Using the & reference opperator to create a new alias or reference to a declared variable.

#include <iostream>

void Increment(int& val)
{
	val++;
}

int main()
{
	int count = 0;
	Increment(count); // This will not change count
	std::cout << "Pointer Count after Increment: " << count << "\n";


	return 0;
}