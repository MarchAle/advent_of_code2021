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

int main()
{
	Map map;
	int	sum = 0;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
		map.push_back(split(line));
	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[i].size(); j++)
		{
			sum += check_surrounding(map, i, j);
		}
		std::cout << std::endl;
	}
	std::cout << sum << std::endl;
}