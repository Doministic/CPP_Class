// Arrays in C++
// Defining and using arrays

#include <iostream>
#include <array>

int main()
{
	// C-Style Array declaration
	int arr1[] = { 1, 2, 3, 4, 5 }; // Array of integers with initial values

	bool arr[8]; // Array of integers with size 8
	// the size of an array indicates how many elements an array can hold

	bool arr2[5]; // Array of booleans with size 5
	// an array with 5 bool values. 

	// Initializing an array
	float arr3[4] = { 1.1, 2.2, 3.3, 4.4 }; // Array of floats with initial values

	// Char array
	char arr4[6] = { 'H', 'e', 'l', 'l', 'o', '\0' }; // Array of characters (C-style string)

	//printing array elements
	std::cout << "arr4 elements:\n";
	for (int i = 0; i < 6; i++)
	{
		std::cout << arr4[i];
	}

	// Accessing array elements
	arr[0] = 10.0f; // Assigning value to the first element 
	arr[1] = 20; // Assigning value to the second element
	arr[2] = 30; // Assigning value to the third element
	arr[4] = 0;

	int countElems = sizeof(arr) / sizeof(arr[0]); // Calculating number of elements in the array

	// Printing array elements
	std::cout << "Array elements:\n";
	for (int i = 0; i < countElems; i++) 
	{
		std::cout << "arr[" << i << "] = " << arr[i] << "\n";
	}

	int arr5[5] = {0, 0, 0, 0, 0}; // Array of integers with size 5, initialized to zero

	std::cout << "arr5 elements: " << arr5[2] << "\n";

	int* arrPtr[5]; // Array of pointers to integers, size 5

	// Initializing an array of pointers
	int a = 10, b = 20, c = 30, d = 40, e = 50;
	arrPtr[0] = &a; // Pointer to a
	arrPtr[1] = &b; // Pointer to b
	arrPtr[2] = &c; // Pointer to c
	arrPtr[3] = &d; // Pointer to nothing (null pointer)
	arrPtr[4] = &e; // Another null pointer

	int countArrPtr = sizeof(arrPtr) / sizeof(arrPtr[0]); // Calculating number of elements in the array of pointers

	std::cout << "arrPtr elements:\n";
	for (int i = 0; i < countArrPtr; i++)
	{
		std::cout << "arrPtr[" << i << "] = " << *arrPtr[i] << "\n"; // Dereferencing pointers to get values
	}

	/*
	* // CPP standard allows arrays to be initialized with a list of values
	*/
	float pi = 3.14f; // Example float variable
	int arr6[5] = { 1, 2, 3, 4, 5 }; // Array of integers with initial values
	std::array<float, 5> arr7 = { 1, 2, 3, 4, pi}; // Using std::array from the C++ Standard Library

	for (int i = 0; i < arr7.size(); i++)
	{
		std::cout << "arr7[" << i << "] = " << arr7[i] << "\n"; // Accessing elements of std::array
	}

	return 0;
}