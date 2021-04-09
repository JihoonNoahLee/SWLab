#include <iostream>
#include <cmath>
#include <fstream>

#define PI 3.141592

using namespace std;

int		main(void)
{
	float		x2, x1, x0;
	float		t, dt;
	ofstream	out("simple_harmonic_motion.txt");

	if (!out)
	{
		cout << "unable to open file 'simple_harmonic_motion'\n";
		return (-1);
	}
	dt = (2 * PI / 10.) / 20.;
	x0 = 0;
	x1 = -20. * dt + x0;
	for (t = 0; t <= 2 * 2 * PI / 10; t += dt)
	{
		x2 = x1 * (2 - 100 * dt * dt) - x0;
		out << t << '\t' << x0 << endl;
		x0 = x1;
		x1 = x2;
	}
	out.close();
	return (0);
}