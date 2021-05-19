#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

float	get_distance(float x1, float y1, float x2, float y2);
float dfabda(float a, float b, float da);
float dfabdb(float a, float b, float db);

float	*datax, *datay;
int		N;

int		main(void)
{
//	Sprint 1
	float	a, b, xi, yi;
	float	AiX, AiY, di;

	a = 1, b = 1;
	xi = 9, yi = 0;
	AiX = xi + a * yi - a * b;
	AiY = AiX * a + b;
	di = get_distance(xi, yi, AiX, AiY);

//	Sprint 4
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

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

//	Sprint 2
float	f(float a, float b)
{
	float	AiX, AiY, di2, sum;

	sum = 0;
	for (int i = 0; i < N; i++)
	{
		AiX = datax[i] + a * datay[i] - a * b;
		AiY = AiX * a + b;
		di2 = pow(AiX - datax[i], 2) + pow(AiY - datay[i], 2);
		sum += di2;
	}
}

//	Sprint 3
float dfabda(float a, float b, float da)
{
	return ((f(a + da, b) - f(a, b)) / da);
}

float dfabdb(float a, float b, float db)
{
	return ((f(a, b + db) - f(a, b)) / db);
}

float	EE(float a, float b, float a_next, float b_next)
{
	return (sqrt(pow(a - a_next, 2) + pow(b - b_next, 2)));
}