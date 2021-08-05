//////////////////////////////
// Author: Doug Young Suh
// Date:   July 12, 2020
//
// class of 2D Gauss dist. 
//////////////////////////////
#include <fstream>
#include <iomanip>
#include <eigen/Dense>
#include <cmath>
using namespace Eigen;
using namespace std;
class Gauss2D {
public:
	Gauss2D() {
		S.Identity();
		Si.Identity();
		det = 1.0;
		mu.Zero();
	};
	Gauss2D(Matrix2f SS) {
		S = SS;
		Si = S.inverse();
		det = S.determinant();
		mu.Zero();
	}
	Gauss2D(Matrix2f SS, Vector2f mumu) {
		S = SS;
		Si = S.inverse();
		det = S.determinant();
		mu = mumu;
	}
	Matrix2f S, Si;
	Vector2f mu;
	const float pi = 3.141592;
	float det;
	float dist2d(const float x1, const float x2) {
		Vector2f x2d = Vector2f(x1, x2);
		float ex = (float)((x2d - mu).transpose() * Si * (x2d - mu));
		return exp(-ex / 2.0) / 2.0 / pi / sqrt(det);
	}
};
int main()
{
	ofstream xcout("dist2d.txt");
	Matrix2f myS;
	//myS << 1.0, 0.0, 0.0, 1.0;
	//myS << 1.0, -0.5, -0.5, 1.0;
	//myS << 1.0, -0.8, -0.8, 1.0;
	myS << 1.0, 0.5,
		-0.5, 2.0;
	Gauss2D mygauss(myS, Vector2f(0.0, 0.0));
	float dx = 0.2;
	// the 1st line
	xcout << "      0         ";
	for (float x2 = -4.0; x2 < 4.0; x2 += dx) {
		xcout << setw(15) << x2 << " ";
	}
	xcout << endl;
	// dist values
	for (float x1 = -4.0; x1 < 4.0; x1 += dx) {
		xcout << setw(15) << x1 << " ";
		for (float x2 = -4.0; x2 < 4.0; x2 += dx) {
			xcout << setw(15) << mygauss.dist2d(x1, x2) << " ";
		}
		xcout << endl;
	}
	xcout.close();

	return 0;
}


