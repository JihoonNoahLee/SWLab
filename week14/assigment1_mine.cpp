#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <Eigen/Dense>
#include <Eigen/LU>
#include "eigen_logistic_regression.h"

using namespace std;
using namespace Eigen;

void	generate_2d_gaussian_data(MatrixXf* mat_X, MatrixXd* mat_T,
						int patterns, int len, float mean1, float mean2, float var);

int		main(void)
{
	int			patterns = 2;
	int			train_N = 400 * patterns;
	int			test_N = 60 * patterns;
	int			nIn = 2, nOut = 2;
	MatrixXf	train_X(train_N, nIn);
	MatrixXd	train_T(train_N, nOut);
	MatrixXf	test_X(test_N, nIn);
	MatrixXd	test_T(test_N, nOut);
	int			epochs = 2000;
	double		learning_rate = 0.2;
	int			mini_batchsize = 50;
	int			mini_batch_N = train_N / mini_batchsize;
	int			epoch;
	MatrixXf	minibatch_x(mini_batchsize, nIn);
	MatrixXd	minibatch_t(mini_batchsize, nOut);

	generate_2d_gaussian_data(&train_X, &train_T, patterns, train_N, -2., 2., 1.);
	generate_2d_gaussian_data(&test_X, &test_T, patterns, test_N, -2., 2., 1.);
	epoch = 0;
	eigen_logistic_regression	classifier = 
				eigen_logistic_regression(nIn, nOut, mini_batchsize);
	for (epoch = 0; epoch < epochs; epoch++)
	{
		for (int n = 0; n < train_N; n += mini_batchsize)
		{
			for (int i = 0; i < mini_batchsize; i++)
			{
				for (int j = 0; j < nIn; j++)
					minibatch_x(i, j) = train_X(n + i, j);
				for (int j = 0; j < nOut; j++)
					minibatch_t(i, j) = train_T(n + i, j);
			}
			classifier.train(minibatch_x, minibatch_t, mini_batchsize, learning_rate);
		}
		learning_rate *= 0.95;
	}
	VectorXd	predicted_T(test_N);
	VectorXf	test_X_row(nIn);
	ofstream	output("gaussian_prediction.txt");

	if (!output)
	{
		cout << "unable to open file 'gaussian_prediction.txt'" << endl;
		return (-1);
	}
	for (int i = 0; i < test_N; i++)
	{
		for (int j = 0; j < nIn; j++)
			test_X_row(j) = test_X(i, j);
		predicted_T = classifier.predict(test_X_row);
		output << test_X(i, 0) << "\t" << test_X(i, 1) << "\t" << predicted_T(0) << "\t" << predicted_T(1) << endl;
	}

	return (0);
}


void	generate_2d_gaussian_data(MatrixXf *mat_X, MatrixXd *mat_T,
						int patterns, int len, float mean1, float mean2, float var)
{
	int						i;
	default_random_engine	generator;
	normal_distribution<double>	g1(mean1, var);
	normal_distribution<double> g2(mean2, var);

	for (i = 0; i < len / patterns; i++)
	{
		(*mat_X)(i, 0) = g1(generator);
		(*mat_X)(i, 1) = g2(generator);
		(*mat_T)(i, 0) = 1;
		(*mat_T)(i, 1) = 0;
	}
	for (i = len / patterns; i < len; i++)
	{
		(*mat_X)(i, 0) = g2(generator);
		(*mat_X)(i, 1) = g1(generator);
		(*mat_T)(i, 0) = 0;
		(*mat_T)(i, 1) = 1;
	}
}