#include <iostream>
#include <time.h>

// File: class01_char.cpp
// This program demonstrates the use of character type in C++
// Chars are the foundational building block of all text in C++
// The char data type is one of the fundatmental data types in C++
// It is used to store single characters, such as letters, digits, and symbols

#pragma warning(disable : 4700)  // ignore

int main()
{

	// Character type in C++
	// char is a data type that can hold a single character
	// It is typically 1 byte in size, which can hold 256 different values (0 to 255)
	std::cout << "Size of char: " << sizeof(char) << " bytes\n";

	// Character literals in C++ are enclosed in single quotes
	std::cout << "Character literal 'A': " << 'A' << "\n";
	
	// Creating a char in C++
	char myChar = 'A';  // single character
	std::cout << "myChar: " << myChar << "\n";

	
	// Different ways of Initialization 
	char a =  97;  // copy initialization (C style initialization)
	char b( 98 );  // direct initialization (Early CPP standard for initialization) 
	char c{ 99 };  // list intialization (C++11 standard initialization)
	
	std::cout << "a: " << a << "\n";
	std::cout << "b: " << b << "\n"; 
	std::cout << "c: " << c << "\n";

	/*
	// What happens when a variable does not have any initialization?
	// This can create indeterminate values if we utilize variables without a propper initilization
	char d; // standard way to initialize a variable
	std::cout << "d: " << d << "\n";  // uninitialized variable, may contain "garbage" value
	*/

	/*
	char ch = 'A';
	std::cout << "The size of a char: " << sizeof(char) << " in Byte(s)\n";
	std::cout << "The size of a char: " << CHAR_BIT << " in Bit(s)\n"; 
	std::cout << "The size of the variable ch: " << ch <<" of type char: " << sizeof(ch) << " in Byte(s)\n";
	*/
	return 0;  // Return 0 to indicate successful execution
}
// End o f class01_char.cpp