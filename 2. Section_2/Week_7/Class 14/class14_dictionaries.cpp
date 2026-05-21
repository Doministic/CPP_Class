
// Dictionaries are a key-value pair
// True name in cpp map
// ordered map & unordered map

#include <iostream>
#include <map>
#include <string>
#include <array>

int main()
{
	std::map<std::string, std::array<std::string, 7>> toyotaCars;

	toyotaCars["Toyota"] = { "Corolla", "Camry", "GR86", "GR Corolla", "Mirai"};

	std::string corollaBodyStyle[3] = { "Sedan", "Hatchback", "Hybrid" };

	std::string selectionMake = "Toyota";
	std::string selectionModel = "Corolla";
	std::string subBodyStyle;

	if ( toyotaCars.find(selectionMake) != toyotaCars.end() )
	{
		std::cout << "Main Func Line 25" << "\n";
		int bodyStyle = -1;
		std::cin >> bodyStyle;

		if (bodyStyle < 0 || bodyStyle >= 3)
		{
			std::cout << "That subModel does not exists";
			return -1;
		}

		switch(bodyStyle)
		{
			case 0:
				subBodyStyle = corollaBodyStyle[0];
				break;
			case 1:
				subBodyStyle = corollaBodyStyle[1];
				break;
			case 2:
				subBodyStyle = corollaBodyStyle[2];
				break;
			default:
				subBodyStyle = "No Body Style Selected";
				break;
		}
			
	}

	std::cout << "The Car you have selected is: " << selectionMake << " " << selectionModel << " " << subBodyStyle;

	return 0;
}
