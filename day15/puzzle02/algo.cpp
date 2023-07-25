#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <list>
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

typedef	struct s_point
{
	int 	x;
	int 	y;
	int		value;
	bool	visited;
	int		distance;
	bool	visited_once;

	bool operator>(const s_point &other) const
	{
		return distance > other.distance;
	}
}	t_point;

typedef std::vector<std::vector<t_point> > Map;

std::vector<std::string> split(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<std::string> result;
	while (getline(ss, tmp, sep))
		result.push_back(tmp);
	return (result);
}

std::vector<t_point>	line_of_points(std::string &line)
{
	std::vector<t_point> new_line_of_points;
	for (size_t i = 0; i < line.size(); i++)
	{
		t_point new_point;
		new_point.value = line[i] - 48;
		new_point.visited = false;
		new_point.visited_once = false;
		new_line_of_points.push_back(new_point);
	}
	return (new_line_of_points);
}

bool	valid_position(Map &map, int x, int y)
{
	if (x < 0 || x >= (int)map[0].size())
		return (false);
	if (y < 0 || y >= (int)map.size())
		return (false);
	return (true);
}

// void	print_map(Map &map)
// {
// 	for (Map::iterator it = map.begin(); it != map.end(); it++)
// 	{
// 		for (std::vector<t_point>::iterator line_it = (*it).begin(); line_it != (*it).end(); line_it++)
// 		{
// 			if ((*line_it).visited == true)
// 				std::cout << GREEN;
// 			std::cout << (*line_it).value << " " << END;
// 		}
// 		std::cout << std::endl;
// 	}
// }


void	next_cell(int &current_dist, Map &map, int x, int y, std::priority_queue<t_point, std::vector<t_point>, std::greater<t_point> > &queue)
{
	int next_dist = current_dist + map[y][x].value;
	if (map[y][x].visited_once == false || next_dist < map[y][x].distance)
	{
		map[y][x].distance = next_dist;
		map[y][x].visited_once = true;
		t_point next_point;
		next_point.x = x;
		next_point.y = y;
		next_point.distance = next_dist;
		queue.push(next_point);
	}
}

void	explore_surroundings_dijkstra(int &current_dist, Map &map, int x, int y, std::priority_queue<t_point, std::vector<t_point>, std::greater<t_point> > &queue)
{
	if (valid_position(map, x + 1, y) == true)
		next_cell(current_dist, map, x + 1, y, queue);
	if (valid_position(map, x, y + 1) == true)
		next_cell(current_dist, map, x, y + 1, queue);
	if (valid_position(map, x - 1, y) == true)
		next_cell(current_dist, map, x - 1, y, queue);
	if (valid_position(map, x, y - 1) == true)
		next_cell(current_dist, map, x, y - 1, queue);
}

int dijkstra(Map &map)
{
	std::priority_queue<t_point, std::vector<t_point>, std::greater<t_point> > queue;
	t_point	first_point;
	first_point.x = 0;
	first_point.y = 0;
	first_point.distance = 0;
	first_point.visited_once = true;
	queue.push(first_point);

	while (!queue.empty())
	{
		t_point current_point = queue.top();
		queue.pop();
		explore_surroundings_dijkstra(current_point.distance, map, current_point.x, current_point.y, queue);
	}

	return (map[map.size() - 1][map[0].size() - 1].distance);
}

void	extend_rows(Map &map)
{
	int line_size = map[0].size();
	for (Map::iterator it = map.begin(); it != map.end(); it++)
	{
		for (int i = 0; i < line_size * 4; i++)
		{
			t_point new_point;
			new_point.visited_once = false;
			new_point.value = (*it)[i].value + 1 > 9 ? 1 : (*it)[i].value + 1;
			(*it).push_back(new_point);
		}
	}
}

std::vector<t_point> copy_line(std::vector<t_point> &line)
{
	std::vector<t_point> new_line;
	std::vector<t_point>::iterator end = line.end();
	for (std::vector<t_point>::iterator it = line.begin(); it != end; it++)
	{
		t_point new_point;
		new_point.visited_once = false;
		new_point.value = (*it).value + 1 > 9 ? 1 : (*it).value + 1;
		new_line.push_back(new_point);
	}
	return (new_line);
}

void	extend_columns(Map &map)
{
	int	column_size = map.size();
	for (int i = 0; i < column_size * 4; i++)
		map.push_back(copy_line(map[i]));
}

void	extend_map(Map &map)
{
	extend_rows(map);
	extend_columns(map);
}

int main()
{
	Map	map;
	int	min_cost;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
		map.push_back(line_of_points(line));
	extend_map(map);
	min_cost = dijkstra(map);
	std::cout << min_cost << std::endl;
}	