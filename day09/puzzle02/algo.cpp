#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
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

typedef std::vector<std::vector<std::pair<int, int> > > Map;

std::vector<std::pair<int, int> > split(std::string &line)
{
	std::vector<std::pair<int, int> > result;
	for (size_t i = 0; i < line.length(); i++)
		result.push_back(std::make_pair(line[i] - 48, 0));
	return (result);
}

void	explore_bassin(Map &map, int y, int x, int bassin_id)
{
	for (int i = -1; i < 2; i += 2)
	{
		if ((y + i >= 0 && y + i < (int)map.size()) && map[y + i][x].first < 9 && map[y + i][x].second == 0)
		{
			map[y + i][x].second = bassin_id;
			explore_bassin(map, y + i, x, bassin_id);
		}
		if ((x + i >= 0 && x + i < (int)map[0].size()) && map[y][x + i].first < 9 && map[y][x + i].second == 0)
		{
			map[y][x + i].second = bassin_id;
			explore_bassin(map, y, x + i, bassin_id);
		}
	}
}

int main()
{
	Map map;
	int bassin_id = 1;
	int	sum = 1;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
		map.push_back(split(line));
	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].first < 9 && map[i][j].second == 0)
			{
				map[i][j].second = bassin_id;
				explore_bassin(map, i, j, bassin_id++);
			}
		}
	}
	std::vector<int> bassin_list(bassin_id, 0);
	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].second != 0)
				bassin_list[map[i][j].second]++;
		}
	}
	std::sort(bassin_list.begin(), bassin_list.end());
	for (int i = 0; i < 3; i++)
		sum *= bassin_list[bassin_id - 1 - i];
	std::cout << sum << std::endl;
}