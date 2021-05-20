#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include <ctime>
#include "Fft1D.h"

using namespace std;

#define PI	3.141592

void	DFT(complex<double>* x_n, complex<double>* X_k, int len);
void	IDFT(complex<double>* x_n, complex<double>* X_k, int len);
void	print_compared_time(int N, int trial);

int		main(void)
{
	int		N = 512;
//	Sprint 1
	complex<double>	z1(1, 2), z2(2, 3), z3[6];

	z3[0] = z1 + z2;
	z3[1] = z1 - z2;
	z3[2] = z1 * z2;
	z3[3] = z1 / z2;
	z3[4] = 3. * z1;
	z3[5] = conj(z1);
	cout << "z1: " << z1 << " z2: " << z2 << endl;
	cout << "z1 + z2 " << z3[0] << endl;
	cout << "z1 - z2 " << z3[1] << endl;
	cout << "z1 * z2 " << z3[2] << endl;
	cout << "z1 / z2 " << z3[3] << endl;
	cout << "3 * z1 " << z3[4] << endl;
	cout << "conj of z1 " << z3[5] << endl;

//	Sprint2
	FFT			*sequence;
	long		n, k;
	ofstream	output("FFTSquare.txt");

	if (!output)
	{
		cout << "unable to open file 'FFTSquare.txt'";
		return (-1);
	}
	sequence = new FFT(N);
	for (n = 0; n < N; n++)			sequence->x[n] = complex<double>(0.0, 0.0);
	for (n = 0; n < 16; n++)		sequence->x[n] = complex<double>(1.0, 0.0);
	for (n = N - 15; n < N; n++)	sequence->x[n] = complex<double>(1.0, 0.0);
	sequence->ForwardFFT();
	for (k = N / 2; k < N - 1; k++)
		output << sequence->X[k].real() << endl;
	for (k = 0; k < N / 2 + 1; k++)
		output << sequence->X[k].real() << endl;
	output.close();

//	Sprint3
	complex<double>*	x_n = new complex<double>[N];
	complex<double>*	X_k = new complex<double>[N];
	ofstream			output1("DFTSquare.txt");

	if (!output1)
	{
		cout << "Unable to open file 'DFTSquare.txt'" << endl;
		return (-2);
	}
	for (n = 0; n < N; n++)			x_n[n] = complex<double>(0.0, 0.0);
	for (n = 0; n < 16; n++)		x_n[n] = complex<double>(1.0, 0.0);
	for (n = N - 15; n < N; n++)	x_n[n] = complex<double>(1.0, 0.0);
	DFT(x_n, X_k, N);
	for (k = N / 2; k < N - 1; k++)
		output1 << X_k[k].real() << endl;
	for (k = 0; k < N / 2 + 1; k++)
		output1 << X_k[k].real() << endl;
	output1.close();

//	Sprint4
	ofstream	output2("IFTSinc.txt");

	if (!output2)
	{
		cout << "Unable to open file 'IFTSinc.txt'" << endl;
		return (-3);
	}
	for (k = 0; k < N; k++)			sequence->X[k] = complex<double>(0.0, 0.0);
	for (k = 0; k < 16; k++)		sequence->X[k] = complex<double>(1.0, 0.0);
	for (k = N - 15; k < N; k++)	sequence->X[k] = complex<double>(1.0, 0.0);
	sequence->InverseFFT();
	IDFT(x_n, X_k, N);
	for (n = 0; n < N; n++)
		output << n << "\t" << sequence->x[n] << "\t" << x_n[n] << endl;
	output2.close();
	delete[] x_n;
	delete[] X_k;
	delete sequence;

//	Sprint5
	N = 128;
	print_compared_time(N, 10000);
	return (0);
}

void	DFT(complex<double> *x_n, complex<double>* X_k, int len)
{
	int				k, n;
	complex<double>	W, z;
	complex<double> j = complex<double>(0., 1.);

	for (k = 0; k < len; k++)
	{
		z = (0.0, 0.0);
		for (n = 0; n < len; n++)
		{
			W = exp(-1. * j *
				complex<double>((double)k * (double)n * (2. * PI / (double)len), 0));
			z += x_n[n] * W;
		}
		X_k[k] = z;
	}
}

void	IDFT(complex<double>* x_n, complex<double>* X_k, int len)
{
	int				k, n;
	complex<double>	W, z;
	complex<double>	j = complex<double>(0., 1.);

	for (n = 0; n < len; n++)
	{
		z = (0., 0.);
		for (k = 0; k < len; k++)
		{
			W = exp(j *
				complex<double>((double)k * (double)n * (2. * PI / (double)len), 0));
			z += X_k[k] * W;
		}
		x_n[n] = z / complex<double>((double)len, 0);
	}
}

void	print_compared_time(int N, int trial)
{
	int					n;
	clock_t				start, end;
	float				time_dft, time_fft;
	complex<double>* x_n = new complex<double>[N];
	complex<double>* X_k = new complex<double>[N];
	FFT* sequence;

	sequence = new FFT(N);
	for (n = 0; n < N; n++)			sequence->x[n] = complex<double>(0.0, 0.0);
	for (n = 0; n < 16; n++)		sequence->x[n] = complex<double>(1.0, 0.0);
	for (n = N - 15; n < N; n++)	sequence->x[n] = complex<double>(1.0, 0.0);
	for (n = 0; n < N; n++)			x_n[n] = complex<double>(0.0, 0.0);
	for (n = 0; n < 16; n++)		x_n[n] = complex<double>(1.0, 0.0);
	for (n = N - 15; n < N; n++)	x_n[n] = complex<double>(1.0, 0.0);
	start = clock();
	for (int i = 0; i < trial; i++)
		sequence->ForwardFFT();
	end = clock();
	time_fft = (float)(end - start) / CLOCKS_PER_SEC;
	start = clock();
	for (int i = 0; i < trial; i++)
		DFT(x_n, X_k, N);
	end = clock();
	time_dft = (float)(end - start) / CLOCKS_PER_SEC;
	cout << "program exec time with length " << N << ": " << endl;
	cout << "Using FFT: " << time_fft << endl;
	cout << "Using DFT: " << time_dft << endl;
	delete[] x_n;
	delete[] X_k;
}