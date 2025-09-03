
#include <iostream>
// #include <cstdint> // For fixed-width integer types like int8_t, int16_t, etc.

// #pragma warnings(disable : 4996) // Disable warnings for unsafe functions like strcpy, sprintf, etc.

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

	std::cout << "Integer declaration - Player's Health: " << health << " takes up: " << sizeof(health) << " Bytes." << static_cast<void*>(&health) << "\n";
	std::cout << "Short declaration - Player's Lives: " << lives << " takes up: " << sizeof(lives) << " Bytes." << static_cast<void*>(&lives) << "\n";
	std::cout << "Long declaratiopn - Player's Score: " << score << " takes up: " << sizeof(score) << " Bytes." << static_cast<void*>(&score) << "\n";
	std::cout << "Long Long declaration - Player's High Score: " << highScore << " takes up: " << sizeof(highScore) << " Bytes." << static_cast<void*>(&highScore) << "\n";
	
	/*
	// Integer literals can be written in different bases
	// Decimal (base 10) - the default base for integers
	int decimal = 42; // 42 in decimal
	// Hexadecimal (base 16) - prefixed with 0x or 0X
	int hexadecimal = 0x2F; // 47 in hexadecimal
	// Octal (base 8) - prefixed with 0
	int octal = 055; // 44 in octal
	// Binary (base 2) - prefixed with 0b or 0B (C++14 and later)
	int binary = 0b101010; // 42 in binary
	std::cout << "Decimal: " << decimal << " located at: " << static_cast<void*>(&decimal) << "\n";
	std::cout << "Hexadecimal: " << std::hex << hexadecimal << " located at: " << static_cast<void*>(&hexadecimal) << "\n";
	std::cout << "Octal: " << octal << " located at: " << static_cast<void*>(&octal) << "\n";
	std::cout << "Binary: " << binary << " located at: " << static_cast<void*>(&binary) << "\n";
	*/


	// When it comes to any numerical value Humans inherently assume positivity or negativity based on the expression of a symbol
	// The compiler does not have that option unless we tell it we want that option
	// This means that a compiler needs to know if a value is signed or unsigned
	// Unsigned means that we do not take into account the signage and assume always positive therefore our number system starts at 0 and ends depending on how much memory we tell the compiler it has for that number
	// Signed means that we have to account for negative values and therefore use one of the bits in memory to keep track of wether a value is positive or negative. 
	// This means that values if signed will not be able to have as large of values as unsigned. 


	/*
	signed int negI = -42; // signed integer, can be negative
	signed int posI = 42; // signed integer, can be positive
	unsigned int posUI = 42; // unsigned integer, can only be positive
	unsigned int negUI = -42; // This would be an error, as unsigned cannot be negative

	std::cout << "Signed Integer: " << negI << " located at: " << static_cast<void*>(&negI) << "\n";
	std::cout << "Signed Integer: " << posI << " located at: " << static_cast<void*>(&posI) << "\n";
	std::cout << "Unsigned Integer: " << posUI << " located at: " << static_cast<void*>(&posUI) << "\n";
	// Note: The size of an int can vary between systems, but it is typically 4 bytes (32 bits) on most modern systems.
	std::cout << "Unsigned Integer: " << negUI << " located at: " << static_cast<void*>(&negUI) << "\n"; // This line would cause a compilation error
	*/


	/*
	// We can also make our integers more specific by using the std::int8_t, std::int16_t, std::int32_t, and std::int64_t types from the <cstdint> header
	// Fixed Width means how much memory we are allocating for that integer

	std::int8_t smallInt = 127; // 8 bits, range: -128 to 127 (notice the signage here)
	std::int16_t mediumInt = 32767; // 16 bits, range: -32768 to 32767
	std::int32_t largeInt = 2147483647; // 32 bits, range: -2147483648 to 2147483647
	std::int64_t extraLargeInt = 9223372036854775807; // 64 bits, range: -9223372036854775808 to 9223372036854775807

	std::cout << "Small Int (int8_t): " << static_cast<int>(smallInt) << " located at: " << static_cast<void*>(&smallInt) << "\n";
	std::cout << "Medium Int (int16_t): " << mediumInt << " located at: " << static_cast<void*>(&mediumInt) << "\n";
	std::cout << "Large Int (int32_t): " << largeInt << " located at: " << static_cast<void*>(&largeInt) << "\n";
	std::cout << "Extra Large Int (int64_t): " << extraLargeInt << " located at: " << static_cast<void*>(&extraLargeInt) << "\n";
	*/

	return 0;  // Return 0 to indicate successful execution
}