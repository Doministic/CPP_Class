
#include <iostream>

int main()
{

	float fireDamage_f = 0.1;
	float iceDamage_f = 0.1;
	float fireResistance_f = 0.1;
	float iceResistance_f = 0.1;

	std::cout << "FireDamage_f: " << fireDamage_f << " " << sizeof(fireDamage_f) << " bytes " << static_cast<void*>(&fireDamage_f) << "\n";
	std::cout << "IceDamage_f: " << iceDamage_f << " " << sizeof(iceDamage_f) << " bytes " << static_cast<void*>(&iceDamage_f) << "\n";
	std::cout << "FireResistance_f: " << fireResistance_f << " " << sizeof(fireResistance_f) << " bytes " << static_cast<void*>(&fireResistance_f) << "\n";
	std::cout << "IceResistance_f: " << iceResistance_f << " " << sizeof(iceResistance_f) << " bytes " << static_cast<void*>(&iceResistance_f) << "\n";

	double fireDamage_d = 0.1;
	double iceDamage_d = 0.1;
	double fireResistance_d = 0.1;
	double iceResistance_d = 0.1;

	std::cout << "FireDamage_f: " << fireDamage_d << " " << sizeof(fireDamage_d) << " bytes " << static_cast<void*>(&fireDamage_d) << "\n";
	std::cout << "IceDamage_f: " << iceDamage_d << " " << sizeof(iceDamage_d) << " bytes " << static_cast<void*>(&iceDamage_d) << "\n";
	std::cout << "FireResistance_f: " << fireResistance_d << " " << sizeof(fireResistance_d) << " bytes " << static_cast<void*>(&fireResistance_d) << "\n";
	std::cout << "IceResistance_f: " << iceResistance_d << " " << sizeof(iceResistance_d) << " bytes " << static_cast<void*>(&iceResistance_d) << "\n";


	return 0;  // Return 0 to indicate successful execution
}