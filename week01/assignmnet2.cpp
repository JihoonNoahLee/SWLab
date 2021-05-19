#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define PI 3.141592

class waveHeader
{
public:
	waveHeader() {};
	int		chunkID, chunkSize, Format, subChunkID, subChunk1size;
	short	audioFormat, numChannels;
	int		sampleRate, byteRate;
	short	blockAlign, bitsPerSample;
	int		subchunk2ID, subChunk2size;
};

int	main(void)
{
//Sprint 1: save Asin(2πft) into array short[44100]
	short	wave[44100];// 실패시 동적할당
	float	t, dt;
	int		f, fs;

	fs = 44100;
	dt = 1. / fs;
	f = 440;
	t = 0.;
	for (int i = 0; i < fs; i++)
	{
		wave[i] = (short)(10000 * sin(2 * PI * f * t));
		t += dt;
	}

//Srpint 2: write short[44100] to biniary file "mydata.wav"
	ofstream	output("myWave.wav", ios::binary | ios::out);

	if (!output)
	{
		cout << "Error opening 'myWave.wav'\n";
		return (-1);
	}
	output.write((char *)wave, sizeof(short) * 44100);
	output.close();

//Sprint 3:	read first 44bytes of "Beatles.wav"
//cout		NumChannels, and modify the value into 1
	ifstream	input("Beatles.wav", ios::binary | ios::in);
	waveHeader	myHeader;

	if (!input)
	{
		cout << "Error opening 'myWave.wav'\n";
		return (-1);
	}
	input.read((char*)&myHeader, sizeof(waveHeader));
	cout << "NumChannels = " << myHeader.numChannels << endl;
	myHeader.numChannels = 1;
	input.close();

//Srpint 4: write 44bytes of header and write short[44100]
	ofstream	output("myWave.wav", ios::binary | ios::out);
	
	if (!output)
	{
		cout << "Error opening 'myWave.wav'\n";
		return (-1);
	}
	output.write((char*)&myHeader, sizeof(waveHeader));
	output.write((char*)wave, sizeof(short) * 44100 * myHeader.numChannels);
	output.close();
	return (0);
}