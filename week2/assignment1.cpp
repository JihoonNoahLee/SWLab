#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.141592

using namespace std;

int main(void)
{
	ofstream	output("sinMult.txt", ios::out);

	if (!output)
	{
		cout << "Cannot open file 'sinMult.txt'\n";
		return (-1);
	}

	float	x = 0, y = 0;
	float	dx, dy;

	dx = 2. * PI / 20.;
	dy = 2. * PI / 20.;
	for (int i = 0; i < 20 + 1; i++)
	{
		x = 0;
		for (int j = 0; j < 20 + 1; j++)
		{
			if (i == 0) output << x << "\t";
			else if (j == 0) output << y << "\t";
			else output << sin(x) * sin(y) << "\t";
			x += dx;
		}
		output << endl;
		y += dy;
	}
	output.close();
	return (0);
}
