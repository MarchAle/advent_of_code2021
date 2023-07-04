#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <cmath>

std::vector<std::string> split(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<std::string> result;
	while (getline(ss, tmp, sep))
	{
		if (tmp.length())
			result.push_back(tmp);
	}
	return (result);
}

int main()
{
	std::vector<std::string> output_digits;
	int	digit_count = 0;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
	{
		output_digits = split(split(line, '|')[1], ' ');
		std::vector<std::string>::iterator end = output_digits.end();
		for (std::vector<std::string>::iterator it = output_digits.begin(); it != end; it++)
		{
			int digit_size = (*it).length();
			if (digit_size != 5 && digit_size != 6)
				digit_count++;	
		}
	}
	std::cout << digit_count << std::endl;
}