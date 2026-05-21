

#ifndef CLASS_ABSTRACTION_H

#include <iostream>
#include <string>

class Vehicle
{
private:
	int year = 0;

	std::string make = "";
	std::string model = "";

	bool canDrive = true;

	const void Print()
	{
		std::cout << "Year: " << this->year << "\nMake: " << make << "\nModel: " << model;
	}

public:
	Vehicle() {}
	Vehicle(int param_year, std::string param_make, std::string param_model)
	{
		year = param_year;
		make = param_make;
		model = param_model;
		Print();
	}
};

class Sedan : public Vehicle 
{
private: 
	int speed = 0;

	const int GetSpeed()
	{
		return speed;
	}

public: 
	Sedan() : Vehicle() { std::cout << "Still need to pick your Make, Model, and Year\n\n"; }
	Sedan(int year, std::string make, std::string model) : Vehicle(year, make, model) {}

	void SetSpeed(int param_speed)
	{
		speed = param_speed;
	}

	void CheckSpeed()
	{
		if (GetSpeed() > 100)
		{
			std::cout << "\n\n\n\n\nYour Speed is: " << GetSpeed() << "\nToo Fast Too Furious\n\n\n\n\n";
		}
		else
		{
			std::cout << "\n\n\n\n\nSafe and Sound... Pass Go collect $200\n\n\n\n\n";
		}
	}
};

#endif