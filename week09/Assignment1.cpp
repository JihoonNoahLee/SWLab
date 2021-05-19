#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

#define MAX_TRIAL	100000.
#define	DICE		5
#define PI			3.141592

float	calc_gausian(float mean, float var, int num);

int		main(void)
{
//	Sprint 1
/*	int			trial = 0, dice_num;
	float		result[6] = { 0, 0, 0, 0, 0, 0 };
	ofstream	output("output.txt");

	if (!output)
	{
		cout << "unable to open file 'output.txt'\n";
		return (-1);
	}
	while (trial < MAX_TRIAL)
	{
		dice_num = rand() % 6;
		result[dice_num] += 1;
		trial++;
	}
	for (int i = 0; i < 6; i++)
		result[i] = result[i] / MAX_TRIAL * 100.;
	cout << "Throwing dice for 10000 trials\n";
	cout << "1: " << result[0] << "%" << endl;
	cout << "2: " << result[1] << "%" << endl;
	cout << "3: " << result[2] << "%" << endl;
	cout << "4: " << result[3] << "%" << endl;
	cout << "5: " << result[4] << "%" << endl;
	cout << "6: " << result[5] << "%" << endl;
	output.close();
*/

//	Sprint 2
	int			trial = 0, dice_num;
	float		result[26];
	ofstream	output("output.txt");

	if (!output)
	{
		cout << "unable to open file 'output.txt'\n";
		return (-1);
	}
	for (int i = 0; i < 26; i++)
		result[i] = 0;
	while (trial < MAX_TRIAL)
	{
		dice_num = 0;
		for (int i = 0; i < DICE; i++)
			dice_num += rand() % 6;
		if (dice_num >= 5 && dice_num <= 30)
			result[dice_num - 5] += 1;
		trial++;
	}
	cout << "Throwing 5 dices for 100000 trials\n";
	for (int i = 0; i < 26; i++)
	{
		result[i] = result[i] / MAX_TRIAL * 100.;
		output << i + 5 << "\t" << result[i] << endl;
		cout << i + 5 << ": " << result[i] << "%" << endl;
	}
	output.close();

//	Sprint 3:
	float		mean_die = 0, square_mean_die = 0;
	float		var_die, mean_dice, var_dice;
	ofstream	output2("output2.txt");

	if (!output2)
	{
		cout << "Unable to open file 'output2.txt'\n";
		return (-2);
	}
	for (int i = 0; i < 6; i++)
	{
		mean_die += (float)i / 6.;
		square_mean_die += pow((float)i, 2) / 6.;
	}
	var_die = square_mean_die - pow(mean_die, 2);
	mean_dice = DICE * mean_die;
	var_dice = sqrt(DICE) * var_die;
	for (int i = 0; i < 26; i++)
		output2 << i + 5 << "\t" << result[i] / 100. << "\t" << calc_gausian(mean_dice, var_dice, i + 5) << endl;
	output2.close();
	return (0);
}

float	calc_gausian(float mean, float var, int num)
{
	return ((1 / sqrt(2 * PI * pow(var, 2))) * exp(-1. * pow((num - mean) / var, 2) / 2.));
}