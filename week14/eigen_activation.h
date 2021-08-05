#pragma once
#include <Eigen/Dense>

using namespace Eigen;

class	activation
{
public:
	static int		step(double x);
	static double	sigmoid(double x);
	static VectorXf	softmax(VectorXf x, int n);
};