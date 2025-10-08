// Pointers 
// using the * pointer, * dereference operator and the & address-of operator
// Talking about grabbing things by reference over by value

#include <iostream>

int main()
{
	// Int pointer (star) pX is set to the address of the variable x
	int len = 5;
	int wid = 10;
	int* x = &len;
	int* y = &wid;

	std::cout << "Value: " << len << "\n";
	std::cout << "X: " << x << "\n";
	std::cout << "Y: " << y << "\n";

	std::cout << "Value: " << wid << "\n";
	std::cout << "X: " << x << "\n";
	std::cout << "Y: " << y << "\n";
	// Int y is set to the derefenced (the thing pointed too) value of pX

	return 0;
}