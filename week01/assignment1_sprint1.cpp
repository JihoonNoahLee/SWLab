#include <iostream>
#include <fstream>
using namespace std;

int	main(void)
{
	ofstream out("textfile.txt");

	if (!out) // if file opening fails
	{
		cout << "Error opening 'textfile.txt'\n";
		return (-1);
	}

	out << "Gugudan 5:\n\n";
	for (int i = 1; i <= 9; i++)
		out << "5 x " << i << " = " << 5 * i << endl;
	return (0);
}