// Pointers 
// using the * pointer, * dereference operator and the & address-of operator
// Talking about grabbing things by reference over by value

#include <iostream>


int* Area_Perimeter(int x, int y)
{
	int* wid = &x;
	int* len = &y;
	
	if (wid == nullptr || len == nullptr) 
	{
		std::cout << "Error: Null pointer passed to Area function.\n";
	}
	int area = *wid * *len; // Calculate area using dereferenced pointers	

	int* pPermeter = new int; // Dynamically allocate memory for perimeter

	// Dereference the pointers to get the values they point to
	return &area;
}

int main()
{
	// Int pointer (star) pX is set to the address of the variable x
	int x = 1;
	int y = 5;

	int* pArea = Area_Perimeter(x, y); // Pass the address of len and wid to Area function

	std::cout << "Area: " << pArea << "\n";

	std::cout << "Value: " << x << "\n";

	std::cout << "Value: " << y << "\n";

	// Int y is set to the derefenced (the thing pointed too) value of pX

	return 0;
}