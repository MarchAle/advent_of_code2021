#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <cmath>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define BRED "\x1B[91m"
# define BGREEN "\x1B[92m"
# define BYELLOW "\x1B[93m"
# define BBLUE "\x1B[94m"
# define BMAGENTA "\x1B[95m"
# define BCYAN "\x1B[96m"
# define WHITE "\x1B[97m"
# define END "\033[0m"

typedef std::vector<std::vector<int> > Map;

std::vector<int> split(std::string &line)
{
	std::vector<int> result;
	for (size_t i = 0; i < line.length(); i++)
		result.push_back(line[i] - 48);
	return (result);
}

int	check_surrounding(Map &map, int y, int x)
{
	int	pos_value = map[y][x];
	// y--; x--;
	for (int i = -1; i < 2; i += 2)
	{
		if ((y + i >= 0 && y + i < (int)map.size()) && map[y + i][x] <= pos_value)
		{
			std::cout << pos_value;
			return (0);
		}
		if ((x + i >= 0 && x + i < (int)map[0].size()) && map[y][x + i] <= pos_value)
		{
			std::cout << pos_value;
			return (0);
		}
	}
	std::cout << BRED << pos_value << END;
	return (1 + pos_value);
}

void	one_step(Map &map)
{
	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[i].size(); j++)
		{
			map[i][j]++;
		}
	}
}

std::vector<std::pair<int, int> > remaining_flashes(Map &map)
{
	std::vector<std::pair<int, int> > flashes_to_execute(0);
	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 10)
				flashes_to_execute.push_back(std::make_pair(i, j));
		}
	}
	return (flashes_to_execute);
}

void	expand_flash(Map &map, int x, int y, int &sum)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (x + i >= 0 && x + i < (int)map.size())
			{
				if (y + j >= 0 && y + j < (int)map[x + i].size())
				{
					if ((i != 0 || j != 0) && map[x + i][y + j] != 0)
					{
						map[x + i][y + j]++;
						if (map[x + i][y + j] == 10)
						{
							map[x + i][y + j] = 0;
							sum++;
							expand_flash(map, x + i, y + j, sum);
						}
					}
				}
			}
		}
	}
}

void	do_flashes(Map &map, int &sum)
{
	std::vector<std::pair<int, int> > flashes_to_execute = remaining_flashes(map);

	while (flashes_to_execute.size() > 0)
	{
		std::vector<std::pair<int, int> >::iterator it = flashes_to_execute.begin();
		for (; it != flashes_to_execute.end(); it++)
		{
			map[(*it).first][(*it).second] = 0;
			expand_flash(map, (*it).first, (*it).second, sum);
			sum++;
		}
		flashes_to_execute = remaining_flashes(map);
	}
}

int	count_flashes(Map &map)
{
	size_t total_flashes = 0;

	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == 0)
			{
				total_flashes++;
				std::cout << BRED << map[i][j] << END;
			}
			else
				std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
	if (total_flashes == map.size() * map[0].size())
		return (1);
	return (0);
}

int main()
{
	Map map;
	int	sum = 0;
	int i = 1;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
		map.push_back(split(line));
	while (1)
	{
		one_step(map);
		do_flashes(map, sum);
		if (count_flashes(map))
		{
			std::cout << std::endl;
			std::cout << i << std::endl;
			return (0);
		}
		std::cout << std::endl;
		i++;
	}
	std::cout << sum << std::endl;
}