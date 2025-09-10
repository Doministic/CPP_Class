

#include <iostream>

int main()
{
	// We are going to look at some things that floats do that are special
	// This is especially true when it comes to division and multiplication.

	float a = 5.0f;  // float literal
	float b = 2.0f;  // float literal

	float c = a / b;  // division
	std::cout << "Dividing " << a << " by " << b << " gives us: " << c << "\n";  // This will print 2.5
	
	float d = a * b;  // multiplication
	std::cout << "Multiplying " << a << " by " << b << " gives us: " << d << "\n";  // This will print 10.0

	return 0;
}