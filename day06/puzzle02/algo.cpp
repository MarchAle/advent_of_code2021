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

void	school_growth(std::vector<unsigned long long> &fishs_infos)
{
	unsigned long long new_fishs = fishs_infos[0];
	for (int i = 0; i < 8; i++)
		fishs_infos[i] = fishs_infos[i + 1];
	fishs_infos[8] = new_fishs;
	fishs_infos[6] += new_fishs;
}

std::vector<unsigned long long>	get_infos(std::vector<int> &fish_school)
{
	std::vector<unsigned long long> infos(8, 0);
	std::vector<int>::iterator end = fish_school.end();
	for (std::vector<int>::iterator it = fish_school.begin(); it != end; it++)
		infos[*it]++;
	return (infos);
}

unsigned long long	total_fishs(std::vector<unsigned long long> &fishs_infos)
{
	unsigned long long total = 0;

	for (int i = 0; i <= 8; i++)
		total += fishs_infos[i];
	
	return (total);
}

int main()
{
	std::vector<int>	fish_school;
	std::vector<unsigned long long>	fishs_infos;
	std::string		line;
	std::ifstream	input("input.txt");
	std::getline(input, line);

	fish_school = split(line, ',');
	fishs_infos = get_infos(fish_school);
	std::cout << "Number of fishs day 0 : " << total_fishs(fishs_infos) << std::endl;

	for (int i = 0; i < 256; i++)
	{
		school_growth(fishs_infos);
		std::cout << "Number of fishs day " << i + 1 << " : " << total_fishs(fishs_infos) << std::endl;
	}
}