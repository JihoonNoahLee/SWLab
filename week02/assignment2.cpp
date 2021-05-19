#include <iostream>
#include <fstream>
// Sprint 2
#include "bmpNew.h"

using namespace std;

int main(void)
{
//	Sprint 1
	unsigned char	*mybmp = new unsigned char [200 * 300 * 3];
	int				red = 0;

	for (int i = 0; i < 200 * 300; i++)
	{
		mybmp[i * 3] = 0;		//B
		mybmp[i * 3 + 1] = 0;	//G
		mybmp[i * 3 + 2] = red;	//R
		if (i % 200 == 0 && red < 255) red++;
	}
//	Srpint 3
	if (!WriteBmp("mybmp.bmp", mybmp, 200, 300))
	{
		cout << "Unable to write file \"mybmp.bmp\"\n";
		return (-1);
	}
//	Sprint 4
	unsigned char*	bmpB;
	int				x, y;

	if (!(bmpB = ReadBmp("sunflower.bmp", &x, &y)))
	{
		cout << "Unable to read file \"sunflower.bmp\"\n";
		return (-2);
	}
	for (int i = 0; i < x * y; i++)
	{
		bmpB[i * 3 + 2] = 0;
	}
	if (!WriteBmp("mysunflower.bmp", bmpB, x, y))
	{
		cout << "Unable to write file \"mysunflower.bmp\"\n";
		return (-3);
	}
	return (0);
}