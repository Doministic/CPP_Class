
#include "header_start.h"

std::string changeString(std::string newS)
{
	newS = "new string new me";
	return newS;
}

int main()
{
	std::cout << header_string << "\n";
	printf(changeString(header_string));

	return 0;
}