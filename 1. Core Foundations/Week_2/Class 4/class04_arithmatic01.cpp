

#include <iostream>

int main()
{
	// Arithmatic Operators
	// addition +
	// subtraction -
	// multiplication *
	// division /
	// modulus %
	// * important note that = and == are not the same thing. 

	// Starting with Char Arithmatic
	char exclaim = '!';  // ASCII value of '!' is 33
	char capA = 'A';  // ASCII value of 'A' is 65
	char lowerB = exclaim + capA;  // ASCII value of 'b' is 98
	std::cout << "Adding ASCII Values: " << exclaim << " + " << capA << "\n";
	std::cout << "Lowercase b: " << lowerB << "\n\n\n";  // This will print a non-printable character

	signed char one = -1;
	signed char two = -2;
	signed char three = one + two;

	std::cout << "Adding the Char Values of 1 and 2 is: " << one << " + " << two << " = " << three << "\n";  // This will print a non-printable character
	// notice how this is prints " " + " " = " " because the ASCII value of 1, 2, and 3 are not printable characters


	std::cout << "Memory locations of one, two, and three:\n";
	std::cout << "one: " << static_cast<void*>(&one) << " and is: " << sizeof(one) << " bytes\n";
	std::cout << "two: " << static_cast<void*>(&two) << " and is: " << sizeof(two) << " bytes\n";
	std::cout << "three: " << static_cast<void*>(&three) << " and is: " << sizeof(three) << " bytes\n\n\n";


	// we will now see the numbers below - this is a way of using an Int to show the decimal value of the char.
	// Notice I am not restating the type since that was stated when I first made the variables on lines 22, 23, and 24
	one = int16_t(one);
	two = int16_t(two);
	three = int16_t(three);

	std::cout << "Adding the Char Values of 1 and 2 is: " << int(one) << " + " << int(two) << " = " << int(three) << "\n";  // This will print the actual numbers. 

	//Here we should see that the memory does not change at all.
	std::cout << "Memory locations of one, two, and three:\n";
	std::cout << "one: " << static_cast<void*>(&one) << " and is: " << sizeof(one) << " bytes\n";
	std::cout << "two: " << static_cast<void*>(&two) << " and is: " << sizeof(two) << " bytes\n";
	std::cout << "three: " << static_cast<void*>(&three) << " and is: " << sizeof(three) << " bytes\n\n\n";

	// Now lets look at the rest of the operands we can use. 
	// Multiplication:
	signed char a = 'a';
	std::cout << "Multiplying a by 2: " << a * 2 << "\n";  // What do you think the outcome is going to be?
	std::cout << "Mulitply the literal expression of 'a' by 2: " << 2 * 'a' << "\n\n\n";  // What about here?

	// Subtraction:
	signed char z = 122;
	signed char questionMark = 63;
	signed char semiColon = z - questionMark;

	// We are looking at a few things here: 
	// Using decimal values in calculations and how that is different in using ASCII
	// How things change when we reverse the variables when we talk about subtraction
	// What is the typing when we subtract?
	std::cout << "Subtraction of z by ASCII Question Mark: " << z << " - " << questionMark << " = " << z - questionMark << "\n";
	std::cout << "Subtraction of the numerical values: " << int(z) << " - " << int(questionMark) << " = " << int(z - questionMark) << "\n";
	std::cout << "Lets reverse this: " << questionMark << " - " << z << " = " << questionMark - z << "\n";
	std::cout << "Reverse of the numerical version : " << int(questionMark) << " - " << int(z) << " = " << int(questionMark - z) << "\n\n\n";

	std::cout << "Subtraction of z by y: " << z << " - " << questionMark << " = " << semiColon << "\n";
	std::cout << "Subtraction of Numerical Value of z by x: " << int(z) << " - " << int(questionMark) << " = " << int(z - questionMark) << "\n";
	std::cout << "Now we will Reverse this: " << questionMark << " - " << z << " = " << semiColon << "\n";
	std::cout << "Now we will Reverse the numeric version: " << int(questionMark) << " - " << int(z) << " = " << int(questionMark - z) << "\n\n\n";

	// Division:
	signed char h = 'h';
	signed char hNum = 104;
	signed char divide = h / hNum;
	signed char divideReverse = hNum / h;

	std::cout << "Divisor h by hNum: " << h << " / " << hNum << " = " << divide << "\n";
	std::cout << "Location of divisor h: " << static_cast<void*>(&h) << "\n";
	std::cout << "Divided By: " << static_cast<void*>(&hNum) << "\n";
	std::cout << "Equals: " << static_cast<void*>(&divide) << "\n\n\n";
	std::cout << "Reverse of Divisor: " << hNum << " / " << h << " = " << divideReverse << "\n";
	std::cout << "Divisor h by hNum: " << h << " / " << hNum << " = " << h / hNum << "\n";
	std::cout << "Reverse of Divisor: " << hNum << " / " << h << " = " << hNum / h << "\n\n\n";

	return 0;
}