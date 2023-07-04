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

void	extract_min_max(int &min, int &max, std::vector<int> &crabs_pos)
{
	std::vector<int>::iterator end = crabs_pos.end();
	for (std::vector<int>::iterator it = crabs_pos.begin(); it != end; it++)
	{
		if (*it < min)
			min = *it;
		else if (*it > max)
			max = *it;
	}
}

int exp_cost(int dist)
{
	int	fuel_used = 1;
	int fuel_cost = 0;
	for (int i = 0; i < dist; i++)
		fuel_cost += fuel_used++;
	return (fuel_cost);
}

int fuel_cost_calcul(int &position, std::vector<int>::iterator it, std::vector<int>::iterator &end)
{
	int cost = 0;
	for (; it != end; it++)
		cost += exp_cost(abs(*it - position));
	return (cost);
}

int	extract_min_fuel_cost(int &min, int &max, std::vector<int> &crabs_pos)
{
	int min_fuel_cost = 0;
	int current_cost;
	std::vector<int>::iterator end = crabs_pos.end();

	for (int i = min; i <= max; i++)
	{
		current_cost = fuel_cost_calcul(i, crabs_pos.begin(), end);
		if (i == min || current_cost < min_fuel_cost)
			min_fuel_cost = current_cost;
	}
	return (min_fuel_cost);
}

int main()
{
	int min, max, min_fuel_cost;
	std::vector<int>	crabs_pos;
	std::string		line;
	std::ifstream	input("input.txt");
	std::getline(input, line);

	crabs_pos = split(line, ',');
	min = max = crabs_pos[0];
	extract_min_max(min, max, crabs_pos);
	min_fuel_cost = extract_min_fuel_cost(min, max, crabs_pos);
	std::cout << "min fuel cost : " << min_fuel_cost << std::endl;
}