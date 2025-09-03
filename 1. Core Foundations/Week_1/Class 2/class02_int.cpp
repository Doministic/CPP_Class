
#include <iostream>

int main()
{

	// Integer type in C++
	// The int type is the most commonly used type in C++
	// Integers take many forms, in games these can be seen as health, countdown timers, scores, etc.

	// basic integer declaration 
	// from now on you will generally see only the copy initialization
	// Ints are generally condsidered 32 bits in size, however, can also be seen as 64 bits, or even 16 bits depending on the system.
	int health = 100; // instantiating a players health

	// a short or short integer is a smaller memory sized int. 
	// taking up less memory, at 16 bits instead of 32, 
	short lives = 3; // instantiating a players lives

	// a long or long integer is a larger memory sized int.
	// taking up more memory, at 64 bits instead of 32,
	long score = 1000000; // instantiating a players score

	// a long long is an even larger memory sized int.
	// taking up even more memory, at 128 bits instead of 64,
	long long highScore = 9999999999; // instantiating a players high score

	std::cout << "Integer declaration - Player's Health: " << health << " takes up: " << sizeof(health) << " Bytes.\n";
	std::cout << "Short declaration - Player's Lives: " << lives << " takes up: " << sizeof(lives) << " Bytes.\n";
	std::cout << "Long declaratiopn - Player's Score: " << score << " takes up: " << sizeof(score) << " Bytes.\n";
	std::cout << "Long Long declaration - Player's High Score: " << highScore << " takes up: " << sizeof(score) << " Bytes.\n";
	

	// Integer literals can be written in different bases
	// Decimal (base 10) - the default base for integers
	int decimal = 42; // 42 in decimal
	// Hexadecimal (base 16) - prefixed with 0x or 0X
	int hexadecimal = 0x2A; // 42 in hexadecimal
	// Octal (base 8) - prefixed with 0
	int octal = 052; // 42 in octal
	// Binary (base 2) - prefixed with 0b or 0B (C++14 and later)
	int binary = 0b101010; // 42 in binary
	std::cout << "Decimal: " << decimal << "\n";
	std::cout << "Hexadecimal: " << std::hex << hexadecimal << "\n";
	std::cout << "Octal: " << std::oct << octal << "\n";
	std::cout << "Binary: " << binary << static_cast<void*>(&binary) << "\n";

	return 0;  // Return 0 to indicate successful execution
}