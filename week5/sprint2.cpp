#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/LU>

using namespace std;
using namespace Eigen;

int	main(void)
{
	Matrix2d	A, AT;
	Vector2d	B, C;
	ifstream	data("datae.txt");
	ofstream	output("sprint2_out.txt");
	int			data_len;

	if (!data || !output)
	{
		cout << "file opening error\n";
		return (-1);
	}
	data >> data_len;

	float* x_arr = new float[data_len];
	float* y_arr = new float[data_len];
	float* logy_arr = new float[data_len];

	for (int i = 0; i < data_len; i++)
	{
		data >> x_arr[i] >> y_arr[i];
		logy_arr[i] = log(abs(y_arr[i]));
	}
	data.close();

	float	x_sum, x2_sum, y_sum, xy_sum;

	x_sum = x2_sum = y_sum = xy_sum = 0;
	for (int i = 0; i < data_len; i++)
	{
		x_sum += x_arr[i];
		x2_sum += pow(x_arr[i], 2);
		y_sum += logy_arr[i];
		xy_sum += x_arr[i] * logy_arr[i];
	}
	A << data_len, x_sum,
		x_sum, x2_sum;
	B << y_sum, xy_sum;
	AT = A.inverse();
	C = AT * B;
	for (int i = 0; i < data_len; i++)
	{
		output << x_arr[i] << "\t" << y_arr[i] << "\t" <<
			exp(C[0] + C[1] * x_arr[i]) << endl;
	}
	output.close();
	return (0);
}
