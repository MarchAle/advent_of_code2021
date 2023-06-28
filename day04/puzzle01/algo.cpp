#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <cmath>

#define NOT_MARKED 0 
#define MARKED 1 

typedef std::vector<std::vector<std::pair<int, int> > > Grid;

std::vector<std::pair<int, int> > split_pair(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<std::pair<int, int> > result;
	while (getline(ss, tmp, sep))
	{
		if (tmp.length())
			result.push_back(std::make_pair(stoi(tmp), NOT_MARKED));
	}
	return (result);
}

std::vector<int> split(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<int> result;
	while (getline(ss, tmp, sep))
		result.push_back(std::stoi(tmp));
	return (result);
}

void	add_grid(std::vector<Grid> &grids, std::ifstream &input)
{
	std::string line;
	std::vector<std::vector<std::pair<int, int> > > grid;
	
	for (int i = 0; i < 5; i++)
	{
		std::getline(input, line);
		grid.push_back(split_pair(line, ' '));
	}
	grids.push_back(grid);
}

int		verify_col(int index, Grid &grid)
{
	for (int i = 0; i < 5; i++)
	{
		if (grid[i][index].second == NOT_MARKED)
			return (0);
	}
	return (1);
}

int		verify_row(int index, Grid &grid)
{
	for (int i = 0; i < 5; i++)
	{
		if (grid[index][i].second == NOT_MARKED)
			return (0);
	}
	return (1);
}

int	winning_grid(int &number, Grid &grid)
{
	int sum = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (grid[i][j].second == NOT_MARKED)
				sum += grid[i][j].first;
		}
	}
	return (sum * number);
}

std::pair<int, int>	mark_number_in_grid(int &number, Grid &grid)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (grid[i][j].first == number)
			{
				grid[i][j].second = MARKED;
				if (verify_col(j, grid) || verify_row(i, grid))
					return (std::make_pair(1, winning_grid(number, grid)));
			}
		}
	}
	return (std::make_pair(0, 0));
}

int main()
{
	std::vector<int> numbers_draw;
	std::vector<Grid> grids;
	std::pair<int, int> result;

	std::string		line;
	std::ifstream	input("input.txt");
	std::getline(input, line);
	numbers_draw = split(line, ',');

	while (std::getline(input, line))
	{
		if (line.length() == 0)
			add_grid(grids, input);
	}

	std::vector<int>::iterator end_numbers = numbers_draw.end();
	for (std::vector<int>::iterator numberIt = numbers_draw.begin(); numberIt != end_numbers; numberIt++)
	{
		std::vector<Grid>::iterator end_grids = grids.end();
		for (std::vector<Grid>::iterator gridIt = grids.begin(); gridIt != end_grids; gridIt++)
		{
			result = mark_number_in_grid(*numberIt, *gridIt);
			if (result.first == 1)
			{
				std::cout << result.second << std::endl;
				exit(0);
			}
		}
	}
}