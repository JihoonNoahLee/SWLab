#include <iostream>
#include <fstream>
#include <complex>
#include "fft1d.h"

using namespace std;

#define	N	1024

class	waveHeader
{
public:
	waveHeader() {};
	int		chunkID, chunkSize, Format, subChunkID, subChunk1size;
	short	audioFormat, numChannels;
	int		sampleRate, byteRate;
	short	blockAlign, bitsPerSample;
	int		subChunk2ID, subChunk2size;
};

int		main(void)
{
	ifstream	my_wave("myWave.wav", ios::binary | ios::in);
	ofstream	output("spectrum.txt");
	FFT			spectrum(N);
	waveHeader	my_header;
	float		fs;
	int			n1sec, j;
	short*		one_sec;

	if (!my_wave || !output)
	{
		cout << "unable to open file ";
		if (!my_wave)
			cout << "'myWave.wav'" << endl;
		else
			cout << "'sectrum.txt'" << endl;
		return (-1);
	}
	my_wave.read((char*)&my_header, sizeof(waveHeader));
	fs = (float)my_header.sampleRate;
	n1sec = my_header.sampleRate * my_header.numChannels;
	n1sec = my_header.sampleRate * my_header.numChannels;
	one_sec = new short[n1sec];
	my_wave.read((char*)one_sec, sizeof(short) * n1sec);
	j = n1sec - N * my_header.numChannels - 100;
	for (int i = 0; i < N; i++)
	{
		spectrum.x[i] = complex<float>((float)one_sec[j + i * 2], 0.);
		output << (float)i / fs << "\t" << (float)one_sec[j + i * 2] << endl;
	}
	spectrum.ForwardFFT();
	for (int i = 0; i < N; i++)
		output << (float)i / (float)N * fs << "\t" << abs(spectrum.X[i]) << endl;
	my_wave.close();
	output.close();
	return (0);
}