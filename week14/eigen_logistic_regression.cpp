#include "eigen_logistic_regression.h"
#include "eigen_activation.h"

void		eigen_logistic_regression::train(MatrixXf X,
					MatrixXd T, int mini_batchsize, double learning_rate)
{
	VectorXf	X_row(nIn);
	VectorXf	predicted_y;

	for (int n = 0; n < mini_batchsize; n++)
	{
		for (int col = 0; col < nIn; col++)
			X_row(col) = X(n, col);
		predicted_y = output(X_row);
		for (int j = 0; j < nOut; j++)
		{
			dY(n, j) = predicted_y(j) - T(n, j);
			for (int i = 0; i < nIn; i++)
				grad_W(j, i) += dY(n, j) * X(n, i);
			grad_b(j) += dY(n, j);
		}
	}
	for (int j = 0; j < nOut; j++)
	{
		for (int i = 0; i < nIn; i++)
			W(j, i) -= learning_rate * grad_W(j, i) / mini_batchsize;
		b(j) -= learning_rate * grad_b(j) / mini_batchsize;
	}
}

VectorXf	eigen_logistic_regression::output(VectorXf x)
{
	activation	my_activ;
	VectorXf	pre_activation(nOut);
	
	for (int i = 0; i < nOut; i++)
		pre_activation(i) = 0;
	for (int j = 0; j < nOut; j++)
	{
		for (int i = 0; i < nIn; i++)
			pre_activation(j) += W(j, i) * x(i);
		pre_activation(j) += b(j);
	}
	return (my_activ.softmax(pre_activation, nOut));
}

VectorXd	eigen_logistic_regression::predict(VectorXf x)
{
	VectorXf	y = output(x);
	VectorXd	t(nOut);
	int			argmax = -1;
	double		max = 0.;

	for (int i = 0; i < nOut; i++)
	{
		if (max < y(i))
		{
			max = y(i);
			argmax = i;
		}
	}
	for (int i = 0; i < nOut; i++)
	{
		if (i == argmax)
			t(i) = 1;
		else
			t(i) = 0;
	}
	return (t);
}
