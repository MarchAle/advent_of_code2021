#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <cmath>

int binToInt(std::vector<std::string> &rate)
{
	int total = 0;
	int pow = 0;

	for (int i = rate[0].length() - 1; i >= 0; i--)
	{
		if (rate[0][i] != '0' || pow != 0)
			total += std::pow((rate[0][i] - 48 ) * 2, pow);
		pow++;
	}
	return (total);
}

std::vector<std::string> filter_oxygen_rate(std::vector<std::string> &oxygen_rate, int index)
{
	std::vector<std::string> stack_one;
	std::vector<std::string> stack_two;

	if (oxygen_rate.size() == 1)
		return (oxygen_rate);

	std::vector<std::string>::iterator end = oxygen_rate.end();
	for (std::vector<std::string>::iterator it = oxygen_rate.begin(); it != end; it++)
	{
		if ((*it)[index] == '0')
			stack_one.push_back((*it));
		else
			stack_two.push_back((*it));
	}

	if (stack_one.size() > stack_two.size() || (stack_one.size() == stack_two.size() && stack_one[0][index] == '1'))
		return (filter_oxygen_rate(stack_one, index + 1));
	else
		return (filter_oxygen_rate(stack_two, index + 1));
}

std::vector<std::string> filter_co2_rate(std::vector<std::string> &co2_rate, int index)
{
	std::vector<std::string> stack_one;
	std::vector<std::string> stack_two;

	if (co2_rate.size() == 1)
		return (co2_rate);

	std::vector<std::string>::iterator end = co2_rate.end();
	for (std::vector<std::string>::iterator it = co2_rate.begin(); it != end; it++)
	{
		if ((*it)[index] == '0')
			stack_one.push_back((*it));
		else
			stack_two.push_back((*it));
	}

	if (stack_one.size() > stack_two.size() || (stack_one.size() == stack_two.size() && stack_one[0][index] == '1'))
		return (filter_co2_rate(stack_two, index + 1));
	else
		return (filter_co2_rate(stack_one, index + 1));
}

int main()
{
	std::vector<std::string> oxygen_rate;
	std::vector<std::string> co2_rate;

	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
	{
		if (line[0] == '1')
			oxygen_rate.push_back(line);
		else
			co2_rate.push_back(line);
	}
	if (oxygen_rate.size() < co2_rate.size() || (oxygen_rate.size() == co2_rate.size() && oxygen_rate[0][0] == '0'))
		oxygen_rate.swap(co2_rate);
	
	oxygen_rate = filter_oxygen_rate(oxygen_rate, 1);
	co2_rate = filter_co2_rate(co2_rate, 1);

	std::cout << binToInt(oxygen_rate) * binToInt(co2_rate) << std::endl;
}