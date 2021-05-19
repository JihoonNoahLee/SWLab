#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#define ITER_MAX 1000

float	gaussian(float x, float y, float muX, float muY, float sigX, float sigY, float peak);
float	fxy(float x, float y);
float	dfxydx(float x, float y, float dx);
float	dfxydy(float x, float y, float dy);
float	EE(float x, float y, float x_next, float y_next);

int		main(void)
{
	int		iter = 0;
	float	psi = 0.001, eta = 0.0001, dx = 0.001, dy = 0.001;
	float	x = 0, y = 1., x_next = 0, y_next = 0.;

	while (EE(x, y, x_next, y_next) > eta && iter < ITER_MAX)
	{
		x = x_next;
		y = y_next;
		x_next -= psi * dfxydx(x, y, dx);
		y_next -= psi * dfxydy(x, y, dy);
		if (iter % 5 == 0)
		{
			cout << setw(10) << x << setw(10) << y << " >> ";
			cout << setw(10) << x_next << setw(10) << y_next << endl;
		}
		iter++;
	}

	return (0);
}

float	gaussian(float x, float y, float muX, float muY, float sigX, float sigY, float peak)
{
	return (peak * exp(-pow((x - muX) / sigX, 2.0) - pow((y - muY) / sigY, 2.0)));
}

float	fxy(float x, float y)
{
	return (gaussian(x, y, 1., 1., 1., 2., 4) + gaussian(x, y, -1., -1., 1., 1., 2.));
}

float	dfxydx(float x, float y, float dx)
{
	return ((fxy(x + dx, y) - fxy(x, y)) / dx);
}

float	dfxydy(float x, float y, float dy)
{
	return ((fxy(x, y + dy) - fxy(x, y)) / dy);
}

float	EE(float x, float y, float x_next, float y_next)
{
	return (sqrt(pow(x - x_next, 2) + pow(y - y_next, 2)));
}