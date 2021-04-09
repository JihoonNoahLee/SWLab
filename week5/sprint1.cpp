#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/LU>

using namespace std;
using namespace Eigen;

int	main(void)
{
//	Sprint 1:
	Matrix3d	A, AT;
	Vector3d	B, C;
	ifstream	data("data2.txt");
	ofstream	output("sprint1_out.txt");
	int			data_len;

	if (!data || !output)
	{
		cout << "file opening error\n";
		return (-1);
	}
	data >> data_len;

	float* x_arr = new float[data_len];
	float* y_arr = new float[data_len];

	for (int i = 0; i < data_len; i++)
		data >> x_arr[i] >> y_arr[i];
	data.close();

	float	x_sum, x2_sum, x3_sum, x4_sum, y_sum, xy_sum, x2y_sum;

	x_sum = x2_sum = x3_sum = x4_sum = y_sum = xy_sum = x2y_sum = 0;
	for (int i = 0; i < data_len; i++)
	{
		x_sum += x_arr[i];
		x2_sum += pow(x_arr[i], 2);
		x3_sum += pow(x_arr[i], 3);
		x4_sum += pow(x_arr[i], 4);
		y_sum += y_arr[i];
		xy_sum += x_arr[i] * y_arr[i];
		x2y_sum += pow(x_arr[i], 2) * y_arr[i];
	}
	A << data_len, x_sum, x2_sum,
		x_sum, x2_sum, x3_sum,
		x2_sum, x3_sum, x4_sum;
	B << y_sum, xy_sum, x2y_sum;
	AT = A.inverse();
	C = AT * B;
	for (int i = 0; i < data_len; i++)
	{
		output << x_arr[i] << "\t" << y_arr[i] << "\t" <<
			C[0] + C[1] * x_arr[i] + C[2] * x_arr[i] * x_arr[i] << endl;
	}
	output.close();
	return (0);
}
