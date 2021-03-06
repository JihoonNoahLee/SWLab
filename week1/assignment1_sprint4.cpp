#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

#define PI 3.141592

int	main(void)
{
	ofstream out("textfile.txt", ios::out);

	if (!out)
	{
		cout << "Error opening 'textfile.txt'\n";
		return (-1);
	}

	float	Asint, t, dt;
	int		f, fs;

	fs = 44100;
	dt = 1.0 / fs;

	for (f = 220; f <= 440; f += 110)
	{
		out << "sine function when f = " << f << "\n\n";
		for (t = 0; t <= 0.01; t += dt)
		{
			Asint = float(10000 * sin(2 * PI * f * t));
			out << left << setw(11) << t << " " << Asint << endl;
		}
		out << endl;
	}

	f = 600;
	out << "sine function when f = " << f << "\n\n";
	for (t = 0; t <= 0.01; t += dt)
	{
		Asint = 10000 * sin(2 * PI * f * t);
		out << left << setw(11) << t << "  " << Asint << endl;
	}
	out << endl;

	return (0);
}