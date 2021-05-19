#include <iostream>
#include <random>
using namespace std;

#define N			10
#define p			0.1
#define MAX_TRIAL	10000

float	factorial(int num)
{
	if (num == 0 || num == 1)
		return (1.0);
	return (num * factorial(num - 1));
}

float	binomial(int n, int k, float pp)
{
	return (factorial(n) / factorial(k) / factorial(n - k) * pow(p, k) * pow(1 - p, n - k));
}

int		main(void)
{
	int		i, k, count;
	float	pk_simu[N + 1], pk_anal[N + 1];
	float	EK_sim = 0, VK_sim = 0, EK_anal = 0, VK_anal = 0;
	float	rand_max;

	rand_max = (float)RAND_MAX;
	for (i = 0; i < N + 1; i++)
		pk_simu[i] = pk_anal[i] = 0.;
	//Analytical Solving
	for (k = 0; k <= N; k++)
	{
		pk_anal[k] = binomial(N, k, p);
		EK_anal += k * pk_anal[k];
		VK_anal += k * k * pk_anal[k];
	}
	VK_anal -= EK_anal * EK_anal;

	//Simulation
	for (i = 0; i < MAX_TRIAL; i++)
	{
		count = 0;
		for (k = 0; k < N; k++)
		{
			if (rand() / rand_max < p)
				count++;
		}
		k = count;
		pk_simu[k] += 1;
		EK_sim += k;
		VK_sim += k * k;
	}
	for (k = 0; k <= N; k++)
		pk_simu[k] /= (float)MAX_TRIAL;
	EK_sim /= (float)MAX_TRIAL;
	VK_sim = VK_sim / (float)MAX_TRIAL - EK_sim * EK_sim;

	//Checking Two values
	cout << "EK " << EK_sim << "  " << EK_anal << endl;
	cout << "VK " << VK_sim << "  " << VK_anal << endl;
	for (k = 0; k <= N; k++)
		cout << k << " " << pk_simu[k] << "  " << pk_anal[k] << endl;
	return(0);
}