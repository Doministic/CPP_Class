#include <iostream>
#include <limits>
#include <climits>

int main()
{

	int a = 42;
	int b(42);
	int c{ 42 };

	char ch = 'A';
	std::cout << sizeof(char) << " " << CHAR_BIT << " " << sizeof(ch) << "\n";

	std::cout << "a: " << a <<  " b: " << b <<  " " << " c: " << c << "\n";
	std::cout << "a " << "b" << "\t" << "c" << "\n";

}