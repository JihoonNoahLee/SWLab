#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
//Sprint 2
#include "bmpNew.h"

using namespace std;
using namespace Eigen;

int		main(void)
{
//	Sprint1
	Matrix2d	A, Ai;

	A << 1, -1,
		1, -3;
	Ai = A.inverse();

//	Sprint2
	unsigned char*	bmp;
	unsigned char*	new_bmp;
	int				size_x, size_y;

	if (!(bmp = ReadBmp("sunflower.bmp", &size_x, &size_y)))
	{
		cout << "cannot open file 'sunflower.bmp'\n" << endl;
		return (-1);
	}
	new_bmp = new unsigned char[3 * size_x * size_y];
	for (int y = 0; y < size_y; y++)
	{
		for (int x = 0; x < size_x; x++)
		{

		}
	}
	WriteBmp("sunflower_modified.bmp", new_bmp, size_x, size_y);
	delete[] bmp;
}