#include <iostream>
#include <cmath>
#include <fstream>

#define PI 3.141592

using namespace std;

int		main(void)
{
	float		x2, x1, x0;
	float		t, dt;
	ofstream	out("under-damped_spring.txt");

	if (!out)
	{
		cout << "unable to open file 'under-damped_spring'\n";
		return (-1);
	}
	dt = (2 * PI / (3 * sqrt(11))) / 20.;
	x0 = 1.;
	x1 = 0 * dt + x0;
	for (t = 0; t <=  2. * 2. * PI / (3 * sqrt(11)); t += dt)
	{
		x2 = x1 * (2 - 2 * dt - 100 * dt * dt) + x0 * (-1 + 2 * dt);
		out << t << '\t' << x0 << endl;
		x0 = x1;
		x1 = x2;
	}
	out.close();
	return (0);
}