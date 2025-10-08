// Bitwise operations
// Operators: & (AND), | (OR), ^ (XOR), ~ (NOT)

#include <iostream>
#include <bitset>


#define FLAG_READ (1 << 0) // 00000001
#define FLAG_WRITE (1 << 1) // 00000010
#define FLAG_EXECUTE (1 << 2) // 00000100

int main()
{
	// real world use case
	int perms = 0; // 00000000 00000000 00000000 00000000 (Permissions starting off at zero)

	// Showing the intial states before we set any permissions
	std::cout << "Initial permissions: " << perms << "\n"; // Output: 0
	std::cout << "Initial permissions in binary: " << std::bitset<8>(perms) << "\n"; // Output: 00000000

	// Show the flag defines and the values the flags represent
	// Flag Read
	std::cout << "FLAG_READ: " << FLAG_READ << "\n"; // Output: 1
	std::cout << "FLAG_READ in binary: " << std::bitset<8>(FLAG_READ) << "\n"; // Output: 00000001

	// Flag Write
	std::cout << "FLAG_WRITE: " << FLAG_WRITE << "\n"; // Output: 2
	std::cout << "FLAG_WRITE in binary: " << std::bitset<8>(FLAG_WRITE) << "\n"; // Output: 00000010

	// Flag Execute
	std::cout << "FLAG_EXECUTE: " << FLAG_EXECUTE << "\n"; // Output: 4
	std::cout << "FLAG_EXECUTE in binary: " << std::bitset<8>(FLAG_EXECUTE) << "\n"; // Output: 00000100

	// Set permissions using bitwise OR
	// |= is a compound assignment operator that combines the current value of perms with the value on the right using bitwise OR
	perms |= FLAG_READ | FLAG_WRITE; // Set read and write permissions by setting the respective bits

	// Permissions will first check the bitwise OR of the FLAG_READ and FLAG_WRITE
	// The FLAG_READ 00000001 and pers 00000000 will result in 00000001
	// The FLAG_WRITE 00000010 and perms 00000001 will result in 00000011
	// The final value of perms will be 00000011, which is 3 in decimal

	std::cout << "Permissions after setting read and write: " << perms << "\n"; // Output: 3
	std::cout << "Permissions in binary: " << std::bitset<8>(perms) << "\n"; // Output: 00000011

	if (perms & FLAG_READ) {
		std::cout << "Read permission is set.\n";
	}
	else {
		std::cout << "Read permission is not set.\n";
	}

	if (perms & FLAG_WRITE) {
		std::cout << "Write permission is set.\n";
	}
	else {
		std::cout << "Write permission is not set.\n";
	}
	
	if (perms & FLAG_EXECUTE) {
		std::cout << "Execute permission is set.\n";
	}
	else {
		std::cout << "Execute permission is not set.\n";
	}

	/*
	// RGB using bitwise operations. 
	// changing the value of red, green, and blue will change the color value.
	int red = 200;
	int green = 100;
	int blue = 50;

	int color = (red << 16) | (green << 8) | blue; // Combine RGB into a single integer

	// The color value is now in the format 0xRRGGBB
	std::cout << "Combined color value (RGB): " << color << "\n"; // Output: 13158600
	*/

	/*
	// Flag and Mask 
	unsigned int flag = 1; // 00000000 00000000 00000000 00000001 in binary
	int mask = 3; // 0011 in binary

	// Bitwise AND

	int and_result = flag & mask; // 0001 in binary, which is 1 in decimal

	std::cout << "Bitwise AND of " << flag << " and " << mask << " is: " << and_result << "\n";

	// Bitwise OR

	int or_result = flag | mask; // 0111 in binary, which is 7 in decimal

	std::cout << "Bitwise OR of " << flag << " and " << mask << " is: " << or_result << "\n";

	// Bitwise XOR

	int xor_result = flag ^ mask; // 0110 in binary, which is 6 in decimal

	std::cout << "Bitwise XOR of " << flag << " and " << mask << " is: " << xor_result << "\n";

	// Bitwise NOT

	unsigned int not_result = ~flag; // 11111111 11111111 11111111 111111010 in binary, which is -6 in decimal

	std::cout << "Bitwise NOT of " << flag << " is: " << not_result << "\n";
	

	// Bitwise left shift
	uint16_t left_shift_result = flag << 1; 

	std::cout << "Bitwise left shift of " << flag << " by 1 is: " << left_shift_result << "\n";

	// Bitwise right shift

	uint16_t right_shift_result = flag >> 1;

	std::cout << "Bitwise right shift of " << flag << " by 1 is: " << right_shift_result << "\n";
	*/

	return 0;
}