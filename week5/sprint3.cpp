#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/LU>

using namespace std;
using namespace Eigen;

int	main(void)
{
	MatrixXd	A(6, 6);
	MatrixXd	AT(6, 6);
	VectorXd	B(6), C(6);
	ifstream	data("4fit_data_5th.txt");
	ofstream	output("sprint3_out.txt");
	int			data_len = 100;

	if (!data || !output)
	{
		cout << "file opening error\n";
		return (-1);
	}

	float* x_arr = new float[data_len];
	float* y_arr = new float[data_len];

	for (int i = 0; i < data_len; i++)
		data >> x_arr[i] >> y_arr[i];
	data.close();

	float Nx1, Nx2, Nx3, Nx4, Nx5, Nx6, Nx7, Nx8, Nx9, Nx10, Ny, Nxy1, Nxy2, Nxy3, Nxy4, Nxy5;
	Nx1 = Nx2 = Nx3 = Nx4 = Nx5 = Nx6 = Nx7 = Nx8 = Nx9 = Nx10 = Ny = Nxy1 = Nxy2 = Nxy3 = Nxy4 = Nxy5 = 0.0;
	for (int i = 0; i < data_len; i++) {
		Nx1 += x_arr[i];
		Nx2 += pow(x_arr[i], 2);
		Nx3 += pow(x_arr[i], 3);
		Nx4 += pow(x_arr[i], 4);
		Nx5 += pow(x_arr[i], 5);
		Nx6 += pow(x_arr[i], 6);
		Nx7 += pow(x_arr[i], 7);
		Nx8 += pow(x_arr[i], 8);
		Nx9 += pow(x_arr[i], 9);
		Nx10 += pow(x_arr[i], 10);
		Ny += y_arr[i];
		Nxy1 += x_arr[i] * y_arr[i];
		Nxy2 += x_arr[i] * x_arr[i] * y_arr[i];
		Nxy3 += (pow(x_arr[i], 3)) * y_arr[i];
		Nxy4 += (pow(x_arr[i], 4)) * y_arr[i];
		Nxy5 += (pow(x_arr[i], 5)) * y_arr[i];
	}
	A << data_len, Nx1, Nx2, Nx3, Nx4, Nx5,
		Nx1, Nx2, Nx3, Nx4, Nx5, Nx6,
		Nx2, Nx3, Nx4, Nx5, Nx6, Nx7,
		Nx3, Nx4, Nx5, Nx6, Nx7, Nx8,
		Nx4, Nx5, Nx6, Nx7, Nx8, Nx9,
		Nx5, Nx6, Nx7, Nx8, Nx9, Nx10;
	B << Ny, Nxy1, Nxy2, Nxy3, Nxy4, Nxy5;
	AT = A.inverse();
	C = AT * B;
	for (int i = 0; i < data_len; i++)
	{
		output << x_arr[i] << "\t" << y_arr[i] << "\t" <<
			C[0] + C[1] * x_arr[i] + C[2] * x_arr[i] * x_arr[i] + C[3] * (pow(x_arr[i], 3)) + C[4] * (pow(x_arr[i], 4)) + C[5] * (pow(x_arr[i], 5)) << endl;
	}
	output.close();
	return (0);
}
