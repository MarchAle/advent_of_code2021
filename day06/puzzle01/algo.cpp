#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <cmath>

std::vector<int> split(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<int> result;
	while (getline(ss, tmp, sep))
		result.push_back(std::stoi(tmp));
	return (result);
}

void	school_growth(std::vector<int> &fish_school)
{
	int new_fish = 0;

	std::vector<int>::iterator end = fish_school.end();
	for (std::vector<int>::iterator it = fish_school.begin(); it != end; it++)
	{
		if (*it == 0)
		{
			*it = 6;
			new_fish++;
		}
		else
			(*it)--;
	}
	for (int i = 0; i < new_fish; i++)
		fish_school.push_back(8);
}

int main()
{
	std::vector<int>	fish_school;
	std::string		line;
	std::ifstream	input("input.txt");
	std::getline(input, line);
	fish_school = split(line, ',');
	for (int i = 0; i < 80; i++)
		school_growth(fish_school);
	std::cout << "Number of fishs : " << fish_school.size() << std::endl;
}