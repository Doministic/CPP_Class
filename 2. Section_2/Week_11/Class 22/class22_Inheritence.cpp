// The Guessing Game in C++
// This is the first version of the guessing game using everything we have learned so far. 

#include "C://Users/dolagle/Desktop/CPP_Class/2. MultiFile_2/Week_12/Class 23/class23_Abstraction.cpp"

class Shapes
{
public:
	Shapes() {} // <- Notice this is a function and does not have a semi-colon at the end. 

	float calculateArea(int numSides, int len, int wid)
	{
		if (numSides == 3)
		{
			return (0.5 * len * wid);
		}
		return len * wid;
	}

	const int GetLength()
	{
		return length;
	}

	const int GetWidth()
	{
		return width;
	}

	void SetLength(int len)
	{
		length = len;
	}

	void SetWidth(int wid)
	{
		width = wid;
	}

private:
	int length = 0;
	int width = 0;
};


class Rectangle : public Shapes
{
public:
	const int GetNumSides()
	{
		return numSides;
	}

private:
	const int numSides = 4;
};

int main()
{
	/*
	Rectangle rect;
	rect.SetWidth(255);
	rect.SetLength(14);

	float area = rect.calculateArea(rect.GetNumSides(), rect.GetLength(), rect.GetWidth());

	std::cout << "The Area of a Rectangle can be calculated by multiplying the length of 1 side, by the width of an adjacent side. \n";
	std::cout << "All Rectangles of any size will always have 4 sides. \n";
	std::cout << "Our Rectangle's Area is: " << area << " units.\n\n\n\n\n\n\n\n\n\n";
	*/

	Sedan sedan(2024, "Honda", "Civic");
	sedan.SetSpeed(160);
	sedan.CheckSpeed();

	Sedan BlankSedan;
	BlankSedan.SetSpeed(50);
	BlankSedan.CheckSpeed();

	std::cout << "Including IOSTREAM from other file. " << "\n";

	return 0;
}
