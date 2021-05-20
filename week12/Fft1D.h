#include <complex>
using namespace std;
#ifndef __FFT
#define __FFT

#define Real double

class FFT               
{
	int N,NU;            // N = 2**NU
	void InitializeFFT();
	void DITFFT(int);   // 1-D decimation-in-time FFT
	complex <double> *W;         // W[k] = exp(-2pi*k/N)

	public:
	FFT(int);               // one dimensional constructor
	FFT(Real *,int);        // one dimensional constructor
	~FFT();

	void ForwardFFT();  // x[n] ==> X[k]
	void InverseFFT();  // X[k] ==> x[n]
	complex <double> *x,*X;
};
#endif
