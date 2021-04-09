#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>

using namespace std;
using namespace Eigen;

void	show_eg_val_vec(MatrixXd A1, int dimension);

int	main(void)
{
	Matrix2d	A1, A2, A3;
	Matrix3d	A4, A5, A6, A7;

	A1 << 1, 2, 2, 1;
	A2 << 4, -1, 2, 1;
	A3 << 0, 1, -2, -3;
	A4 << 5, 2, 0, 2, 5, 0, -3, 4, 6;
	A5 << 4, -1, 6, 2, 1, 6, 2, -1, 8;
	A6 << 2, 1, 0, 1, 2, 1, 0, 1, 2;
	A7 << 3, 2, 4, 2, 0, 2, 4, 2, 3;
	show_eg_val_vec(A1, 2);
	show_eg_val_vec(A2, 2);
	show_eg_val_vec(A3, 2);
	show_eg_val_vec(A4, 3);
	show_eg_val_vec(A5, 3);
	show_eg_val_vec(A6, 3);
	show_eg_val_vec(A7, 3);
	return (0);
}

void	show_eg_val_vec(MatrixXd mat, int dimension)
{
	MatrixXd				P(dimension, dimension);
	EigenSolver<MatrixXd>	es;

	es.compute(mat);
	cout << "The eigenvalues of matrix are: " << endl << es.eigenvalues() << endl;
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			P(i, j) = es.eigenvectors()(i, j).real();
	cout << "\nP\n" << P << "\n\n\n";
}