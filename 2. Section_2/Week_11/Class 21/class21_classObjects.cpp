// The Guessing Game in C++
// This is the first version of the guessing game using everything we have learned so far. 

#include <iostream>

class Shapes
{
private: 
	int numSides = 0;	

public:
	Shapes(int numS)
	{
		numSides = numS;
	}

	~Shapes(){}

	int calculateArea(int* numSide, int len, int wid)
	{
		int sideCount = *numSide;
		if (sideCount == 3)
		{
			return 0.5 * (len * wid);
		}
		return len * wid;
	}

	int* pSideCount = &numSides;
};

int main()
{
	Shapes rectangle(4);
	int lengthRec = rectangle.calculateArea(rectangle.pSideCount, 2, 5);
	std::cout << "Length: " << lengthRec << "\n\n";

	Shapes triangle(3);
	int lengthTri = triangle.calculateArea(rectangle.pSideCount, 2, 5);
	std::cout << "Length: " << lengthTri;

	return 0;
}
