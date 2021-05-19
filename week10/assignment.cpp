#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>
#include <random>

using namespace std;
using namespace Eigen;

#define PI	3.141592

#define N	20
#define L	1000

#define	MEAN	0.0
#define	STD_DEV	0.3

int		main(void)
{
//	Sprint 1
	VectorXf	c0t(N), c1t(N), s(N);
	VectorXf*	s_stream = new VectorXf[L];
	float const	T = 20., dt = T / N;
	float		t = dt;
	int			*a, *b;

	for (int i = 0; i < N; i++, t += dt)
	{
		c0t[i] = sqrt(2. / T) * cos(2 * PI * t / T);
		c1t[i] = sqrt(2. / T) * sin(2 * PI * t / T);
	}
	cout << "c0t.dot(c0t)\n" << c0t.dot(c0t) << "\n\n";
	cout << "c1t.dot(c1t)\n" << c1t.dot(c1t) << "\n\n";
	cout << "c0t.dot(c1t)\n" << c0t.dot(c1t) << "\n\n";
	a = new int[L];
	b = new int[L];
	for (int i = 0; i < L; i++)
	{
		a[i] = rand() % 2;
		b[i] = rand() % 2;
	}
	for (int i = 0; i < L; i++)
		s_stream[i] = a[i] * c0t + b[i] * c1t;

	//	Sprint 2
	VectorXf					n(N), r(N);
	VectorXf*					n_stream = new VectorXf[L];
	VectorXf*					r_stream = new VectorXf[L];
	default_random_engine		generator;
	normal_distribution<double>	dist(MEAN, STD_DEV);
	ofstream					output("output1.txt");

	if (!output)
	{
		cout << "unable to open file 'output1.txt'\n";
		return (-1);
	}
	for (int i = 0; i < N; i++)
		n[i] = dist(generator);
	r = s + n;
	for (int i = 0; i < N; i++)
		output << i << "\t" << s[i] << "\t" << r[i] << endl;
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < N; j++)
		{
			n[j] = dist(generator);
		}
		n_stream[i] = n;
		r_stream[i] = n + s_stream[i];
	}
	output.close();

//	Sprint 3
	float		a_prime[L], b_prime[L];
	ofstream	output1("output2.txt");

	if (!output1)
	{
		cout << "unable to open file 'output2.txt'";
		return (-2);
	}
	for (int i = 0; i < L; i++)
	{
		a_prime[i] = r_stream[i].dot(c0t);
		b_prime[i] = r_stream[i].dot(c1t);
	}
	output1 << "a:" << endl;
	for (int i = 0; i < L; i++)
		output1 << i << "\t" << a[i] << "\t" << a_prime[i] << endl;
	output1 << endl << "b:" << endl;
	for (int i = 0; i < L; i++)
		output1 << i << "\t" << b[i] << "\t" << b_prime[i] << endl;
	output1.close();

//	Sprint 4
	int		biterror = 0;
	float	BER;

	for (int i = 0; i < L; i++)
	{
		if (a[i] != floor(a_prime[i] + 0.5)) biterror++;
		if (b[i] != floor(b_prime[i] + 0.5)) biterror++;
	}
	BER = (float)biterror / (2. * L);
	cout << "\n\nbiterror: " << biterror << "\nBER: " << BER << endl;
	delete[] a;
	delete[] b;
	return (0);
}