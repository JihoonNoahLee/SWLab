#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define PI 3.141592
#define ITER_MAX 1000

float	fxy(float x, float y);
float	dfxydx(float x, float y, float dx);
float	dfxydy(float x, float y, float dy);
float	EE(float x, float y, float x_next, float y_next);

int main(void)
{
//	Sprint 1:
	float	minmaxX[4] = { 0.250, 0.250, 0.750, 0.750 };
	float	maxY[4] = { 0.125, 0.625, 0.375, 0.875 };
	float	minY[4] = { 0.375, 0.875, 0.125, 0.625 };

	cout << "max value: \n";
	for (int i = 0; i < 4; i++)
		cout << setw(5) << fxy(minmaxX[i], maxY[i]);
	cout << "\n\nmin value: \n";
	for (int i = 0; i < 4; i++)
		cout << setw(5) << fxy(minmaxX[i], minY[i]);
	cout << "\n\n\n";
//	Sprint 3
	int		iter = 0;
	float	psi = 0.001, eta = 0.0001, dx = 0.01, dy = 0.01;
	float	x = 0, y = 1., x_next = 0, y_next = 0., x_start;

	for (int i = 1; i <= 5; i++)
	{
		x_start = 1.0 / 5 * i;
		for (int j = 1; j <= 5; j++)
		{
			x_next = x_start;
			y_next = 1.0 / 5 * j;
			iter = 0;
			cout << "sarting at x : " << x_next << " y : " << y_next << "\n\n";
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
			cout << "minimum at iter " << iter << " , E = " << EE(x, y, x_next, y_next) << "\n\n";
		}
	}
	getchar();
	return (0);
}

//Sprint 1:
float	fxy(float x, float y)
{
	return (sin(2 * PI * 1 * x) * sin(2 * PI * 2 * y));
}

//Sprint 2:
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