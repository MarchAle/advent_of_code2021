#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <list>
#include <cmath>
#include <bitset>
#include <string>
#include <algorithm>

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

typedef struct s_area
{
	int min_x;
	int min_y;
	int max_x;
	int max_y;
}	t_area;

typedef struct s_pos
{
	int x;
	int y;
}	t_pos;

std::vector<int> split(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<int> result;
	while (getline(ss, tmp, sep))
	{
		if (tmp.length())
			result.push_back(std::stoi(tmp));
	}
	return (result);
}

t_area	get_area(std::string &input)
{
	t_area new_area;
	std::vector<int> tmp;

	for (size_t i = 0; i < input.length(); i++)
	{
		if (!(std::isdigit(input[i]) || input[i] == '-'))
			input[i] = ' ';
	}
	tmp = split(input, ' ');
	new_area.min_x = tmp[0];
	new_area.max_x = tmp[1];
	new_area.max_y = tmp[2];
	new_area.min_y = tmp[3];
	return (new_area);
}

void	velocity_update(int &vel_x, int &vel_y)
{
	if (vel_x > 0)
		vel_x--;
	else if (vel_x < 0)
		vel_x++;
	vel_y--;
}

int		area_check(t_pos &position, t_area &area)
{
	if (position.x > area.max_x || position.y < area.max_y)
		return (-1);
	if (position.x >= area.min_x && position.y <= area.min_y)
		return (1);
	return (0);
}

std::pair<int, int>		test_param(int vel_x, int vel_y, t_area &area)
{
	t_pos 	position;
	int		max_y = 0;
	int		result;
	position.x = 0;
	position.y = 0;

	while (1)
	{
		position.x += vel_x;
		position.y += vel_y;
		max_y = position.y > max_y ? position.y : max_y;
		velocity_update(vel_x, vel_y);
		result = area_check(position, area);
		if (result != 0)
			return (std::make_pair(result, max_y));
	}
	return (std::make_pair(0, 0));
}

int main()
{
	t_area			area;
	int				count = 0;
	std::string		line;
	std::string		packet;
	std::ifstream	input("input.txt");
	std::getline(input, line);
	area = get_area(line);
	for (int i = 0; i < 500; i++)
	{
		for (int j = -500; j < 500; j++)
		{
			std::pair<int, int> result = test_param(i, j, area);
			if (result.first == 1)
				count++;
		}
	}
	std::cout << BGREEN << count << END << std::endl;
}