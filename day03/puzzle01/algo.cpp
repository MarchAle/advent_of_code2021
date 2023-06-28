#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <cmath>

int binToInt(std::vector<int> &rate)
{
	int total = 0;
	int pow = 0;

	for (int i = rate.size() - 1; i >= 0; i--)
	{
		if (rate[i] != 0 || pow != 0)
			total += std::pow(rate[i] * 2, pow);
		pow++;
	}

	return (total);
}

int main()
{
	std::vector<int> gamma_rate;
	std::vector<int> epsilon_rate;
	std::vector<int> total_bytes;
	for (int i = 0; i < 12; i++)
	{
		total_bytes.push_back(0);
		gamma_rate.push_back(0);
		epsilon_rate.push_back(0);
	}

	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
	{
		for (int i = 0; i < 12; i++)
		{
			if (line[i] == '1')
				total_bytes[i] += 1;
			else
				total_bytes[i] -= 1;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if (total_bytes[i] > 0)
			gamma_rate[i] = 1;
		else
			epsilon_rate[i] = 1;
	}

	std::cout << binToInt(gamma_rate) * binToInt(epsilon_rate) << std::endl;
}