#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <Eigen/Dense>
#include <Eigen/LU>
#include "eigen_logistic_regression.h"

using namespace std;
using namespace Eigen;
void get_iris_data(MatrixXf* tnt_X, MatrixXd* tnt_T, MatrixXf* tet_X, MatrixXd* tet_T);

int	patterns = 3;
int	main(void)
{
	int	train_N = 40 * patterns;
	int	test_N = 10 * patterns;
	int	nIn = 4, nOut = 3;
	MatrixXf train_X(train_N, nIn);
	MatrixXd train_T(train_N, nOut);
	MatrixXf test_X(test_N, nIn);
	MatrixXd test_T(test_N, nOut);

	get_iris_data(&train_X, &train_T, &test_X, &test_T);

	int	epochs = 2000;
	double learning_rate = 0.2;

	int	mini_batchsize = 10;
	int	mini_batch_N = train_N / mini_batchsize;

	int	epoch;
	MatrixXf minibatch_x(mini_batchsize, nIn);
	MatrixXd minibatch_t(mini_batchsize, nOut);
	VectorXd predicted_T(test_N);
	MatrixXd predicted_T_M(test_N, nOut);
	VectorXf test_X_row(nIn);
	epoch = 0;
	eigen_logistic_regression	classifier = eigen_logistic_regression(nIn, nOut, mini_batchsize);
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
	for (int i = 0; i < test_N; i++) {
		for (int j = 0; j < nIn; j++)
			test_X_row(j) = test_X(i, j);
		predicted_T = classifier.predict(test_X_row);
		for (int j = 0; j < nOut; j++)
			predicted_T_M(i, j) = predicted_T(j);
	}

	MatrixXd confusionMatrix(patterns, patterns);
	double accuracy = 0.;
	VectorXd precision(patterns);
	VectorXd recall(patterns);
	for (int i = 0; i < patterns; i++) {
		precision[i] = recall[i] = 0;
		for (int j = 0; j < patterns; j++) confusionMatrix(i, j) = 0;
	}
	
	for (int i = 0; i < test_N; i++) {
		int predicted_, actual_;
		for (predicted_ = 0; predicted_ < patterns; predicted_++) if (predicted_T_M(i, predicted_) == 1) break;
		for (actual_ = 0; actual_ < patterns; actual_++) if (test_T(i, actual_) == 1) break;
		if (actual_ == patterns || predicted_ == patterns) {
			cout << "no decision " << predicted_ << " " << actual_ << endl;
			exit(123);
		}
		confusionMatrix(actual_, predicted_) += 1;
	}

	for (int i = 0; i < patterns; i++) {
		double col_ = 0.;
		double row_ = 0.;
		for (int j = 0; j < patterns; j++) {
			if (i == j) {
				accuracy += confusionMatrix(i, j);
				precision[i] += confusionMatrix(i, j);
				recall[i] += confusionMatrix(i, j);
			}
			col_ += confusionMatrix(i, j);
			row_ += confusionMatrix(i, j);
		}
		precision[i] /= col_;
		recall[i] /= row_;
	}
	accuracy /= test_N;

	cout << "------------------------------------\n";
	cout << "Logistic Regression model evaluation\n";
	cout << "------------------------------------\n";
	cout << "Accuracy: " << accuracy * 100 << "\n";
	cout << "Precision:\n";
	for (int i = 0; i < patterns; i++) {
		cout << " class " << i + 1 << ":" << precision[i] * 100 << "\n";
	}
	cout << "Recall:\n";
	for (int i = 0; i < patterns; i++) {
		cout << " class " << i + 1 << ":" << recall[i] * 100 << "\n";
	}
	return (0);
}


void get_iris_data(MatrixXf* tnt_X, MatrixXd* tnt_T, MatrixXf* tet_X, MatrixXd* tet_T) {
	ifstream iris_data("iris_data.txt");
	int it;

	if (!iris_data)
	{
		cout << "Unable to open 'iris_data.txt'" << endl;
		exit (-2);
	}
	for (int k = 0; k < patterns; k++) {
		int m = k * 40;
		for (int i = 0; i < 40; i++, m++) {
			iris_data >> (*tnt_X)(m, 0) >> (*tnt_X)(m, 1) >> (*tnt_X)(m, 2) >> (*tnt_X)(m, 3);
			iris_data >> it;
			for (int j = 0; j < patterns; j++) (*tnt_T)(m, j) = 0; (*tnt_T)(m, it) = 1;
		}
		m = k * 10;
		for (int i = 0; i < 10; i++, m++) {
			iris_data >> (*tet_X)(m, 0) >> (*tet_X)(m, 1) >> (*tet_X)(m, 2) >> (*tet_X)(m, 3);
			iris_data >> it;
			for (int j = 0; j < patterns; j++) (*tet_T)(m, j) = 0; (*tet_T)(m, it) = 1;
		}
	}
}