#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int	main(void)
{
	ofstream out("textfile.txt");

	if (!out)
	{
		cout << "Error opening 'textfile.txt'\n";
		return (-1);
	}

	out << "power of 2:\n\n";
	for (int i = 0; i <= 10; i++)
		out << i << " " << pow(2, i) << endl;
	return (0);
}