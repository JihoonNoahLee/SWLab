#pragma once
#include <Eigen/Dense>

using namespace Eigen;

class	eigen_logistic_regression {
public:
	int			nIn;
	int			nOut;
	int			mini_batchsize;
	MatrixXf	W;
	MatrixXf	grad_W;
	MatrixXf	dY;
	VectorXf	b;
	VectorXf	grad_b;

	eigen_logistic_regression(int _nIn, int _nOut, int _mini_batchsize)
	{
		int		i, j;

		nIn = _nIn;
		nOut = _nOut;
		mini_batchsize = _mini_batchsize;
		W.resize(nOut, nIn);
		grad_W.resize(nOut, nIn);
		b.resize(nOut);
		grad_b.resize(nOut);
		dY.resize(mini_batchsize, nOut);
		for (i = 0; i < nOut; i++)
		{
			b(i) = 0.1;
			grad_b(i) = 0.;
			for (j = 0; j < nIn; j++)
			{
				W(i, j) = 1.;
				grad_W(i, j) = 0.;
			}
		}
	}
	void		train(MatrixXf X, MatrixXd T, int mini_batchsize, double learning_rate);
	VectorXf	output(VectorXf x);
	VectorXd	predict(VectorXf x);
};