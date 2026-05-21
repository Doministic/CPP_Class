// The Guessing Game in C++
// This is the first version of the guessing game using everything we have learned so far. 

#include <iostream>
#include <string>

struct Vehicle {
	std::string make = "";
	std::string model = "";
	std::string type[4] = {"Sedan", "SUV", "Truck", "Motorcycle"};
	int year = 0;
	int numWheels = 0;
	int numDoors = 0;
	bool hasClutch = false;
	bool canDrive = true;
};

int main()
{
	Vehicle sedan;
	
	sedan.make = "Honda";
	sedan.model = "Civic";
	sedan.year = 2013;
	sedan.hasClutch = true;
	sedan.numWheels = 4;

	bool inAccident = false;

	if (inAccident == true)
	{
		sedan.canDrive == false;
	}

	return 0;
}