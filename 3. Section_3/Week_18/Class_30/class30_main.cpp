

#include <iostream>


/*
// int i = -1; // global scope

void foo()
{
	//int i = 100; // foo function scope for i 

	//std::cout << "Scope of foo i: " << i << "\n";

	for (int i = 0; i < 105; i++) // for loop scope for i
	{
		std::cout << i << "\n";
		int j = 0;
		for (j; j < 6; j++)
		{

		}
		j += 2; 
	}

	{
		int i = 50;
		i += 2;
		std::cout << i;
	}
}

*/

struct Dog 
{
	std::string breed = "";
	int age = 0;
	bool isAlive = true;
	int legs = 4;
	std::string furType = "";
	std::string eyeColor = "";
	
};

int main()
{
	
	Dog doggy;
	std::cout << &doggy;
	doggy.breed = "Corgi";
	doggy.age = 5;
	doggy.furType = "smooth";
	doggy.eyeColor = "Brown";

	return 0;
}