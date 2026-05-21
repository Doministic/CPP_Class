// Vectors in C++
// Vectors are dynamic arrays that can grow and shrink in size 

#include <iostream>

int main()
{
	const char wasd[5] = {'w', 'a', 'd', 's'}; // w = (0,1), a = (-1,0), d = (1,0), s = (-1, 0)
	const char* lName[5] = { "Lagle" };

	std::cout << "First Name: " << wasd << std::endl;
	std::cout << "Last Name: " << lName << std::endl;


	return 0;
}