#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void	show_matrix(int M, int N, float* mat);
void	matrix_mult(int N, int M, int P, float* A, float* B, float* C);
void	transpose(int N, int M, float* A, float* AT);

int		main(void)
{
//	Sprint 1:
/*	float	A[] = { 1., 2., 3., 4., 5., 6. };

	show_matrix(2, 3, A);
	show_matrix(3, 2, A);
*/

//	Sprint 2:
/*	float	A[6] = { 1., 2., 3., 4., 5., 6. };
	float	B[4] = { 1.,2.,3.,4. };
	float	C[6];
	
	matrix_mult(3, 2, 2, A, B, C);
	show_matrix(3, 2, C);
*/

//	Sprint 3:
/*
	float	C[16] =	{	0.5,0.5,0.5,0.5,
						0.5,0.5,-0.5,-0.5,
						0.5,-0.5,-0.5,0.5,
						0.5,-0.5,0.5,-0.5 };
	float*	c0, * c1, * c2, * c3;
	float	delta[16];

	c0 = C; c1 = C + 4; c2 = C + 8; c3 = C + 12;
	matrix_mult(1, 4, 1, c0, c0, delta);
	matrix_mult(1, 4, 1, c0, c1, delta + 1);

	cout << "delta[0] : "<< delta[0] << "\ndelta[1] : "<< delta[1] << endl;
*/

//	Sprint 4:

	float	C[16] = {	0.5,0.5,0.5,0.5,
						0.5,0.5,-0.5,-0.5,
						0.5,-0.5,-0.5,0.5,
						0.5,-0.5,0.5,-0.5 };
	float	CT[16];
/*	float	product[16];

	transpose(4, 4, C, CT);
	show_matrix(4, 4, CT);
	matrix_mult(4, 4, 4, C, CT, product);
	show_matrix(4, 4, product);
*/

//	Sprint 5:
	float	a0[] = { 100, 120, -4, 2 };
	float	a1[] = { 100, 20, 120, 32 };
	float	a2[] = { 10, 120, 108, 8 };
	float	Ca0[4], Ca1[4], Ca2[4];

	matrix_mult(4, 4, 1, C, a0, Ca0);
	show_matrix(4, 1, Ca0);
	matrix_mult(4, 4, 1, C, a1, Ca1);
	show_matrix(4, 1, Ca1);
	matrix_mult(4, 4, 1, C, a2, Ca2);
	show_matrix(4, 1, Ca2);
	cout << endl;

//	Sprint 6:
	transpose(4, 4, C, CT);
	//matrix_mult(4, 4, 1, CT, Ca0, a0);
	//show_matrix(4, 1, a0);
	//matrix_mult(4, 4, 1, CT, Ca1, a1);
	//show_matrix(4, 1, a1);
	//matrix_mult(4, 4, 1, CT, Ca2, a2);
	//show_matrix(4, 1, a2);
	cout << endl;

//	Sprint 7:
	a0[2] = a0[3] = 0.;
	a1[1] = a1[2] = 0.;
	a2[1] = a2[3] = 0.;

	matrix_mult(4, 4, 1, C, a0, Ca0);
	show_matrix(4, 1, Ca0);
	matrix_mult(4, 4, 1, C, a1, Ca1);
	show_matrix(4, 1, Ca1);
	matrix_mult(4, 4, 1, C, a2, Ca2);
	show_matrix(4, 1, Ca2);
	cout << endl;

	matrix_mult(4, 4, 1, CT, Ca0, a0);
	show_matrix(4, 1, a0);
	matrix_mult(4, 4, 1, CT, Ca1, a1);
	show_matrix(4, 1, a1);
	matrix_mult(4, 4, 1, CT, Ca2, a2);
	show_matrix(4, 1, a2);
	cout << endl;

//	Sprint 8:
	ofstream	output("output", ios::out | ios::binary);

	if (!output)
	{
		cout << "Unable to opne file 'output'" << endl;
		return (-1);
	}
	output.write((char*)a0, sizeof(float) * 4);
	output.write((char*)a1, sizeof(float) * 4);
	output.write((char*)a2, sizeof(float) * 4);
	output.close();
	show_matrix(4, 1, a0);
	show_matrix(4, 1, a1);
	show_matrix(4, 1, a2);
	return (0);
}

void	show_matrix(int M, int N, float* mat)
{
	int		rows;

	cout << "Matrix: " << endl;
	for (int m = 0; m < M; m++)
	{
		rows = m * N;
		for (int n = 0; n < N; n++)
		{
			cout << setw(6) << mat[rows + n];
		}
		cout << endl;
	}
}

void	matrix_mult(int N, int M, int P, float* A, float* B, float* C)
{
	float	sum;
	for (int n = 0; n < N; n++)
	{
		for (int p = 0; p < P; p++)
		{
			sum = 0;
			for (int m = 0; m < M; m++)
				sum += A[n * M + m] * B[m * P + p];
			C[n * P + p] = sum;
		}
	}
}

void	transpose(int N, int M, float* A, float* AT)
{
	int rows;

	for (int n = 0; n < N; n++)
	{
		rows = M * n;
		for (int m = 0; m < M; m++)
			AT[m * N + n] = A[rows + m];
	}
}
