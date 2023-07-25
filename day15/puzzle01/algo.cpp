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

// void	explore_map(Map &map, int x, int y, int &cost, int &min_cost);

bool	min_cost_initialized = false;

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

// bool	end_position(Map &map, size_t x, size_t y)
// {
// 	if (x == map[0].size() - 1 && y == map.size() - 1)
// 		return (true);
// 	return (false);
// }

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

// void	explore_surroundings(Map &map, int x, int y, int &cost, int &min_cost)
// {
// 	if (valid_position(map, x + 1, y) == true && map[y][x + 1].visited == false)
// 		explore_map(map, x + 1, y, cost, min_cost);
// 	if (valid_position(map, x, y + 1) == true && map[y + 1][x].visited == false)
// 		explore_map(map, x, y + 1, cost, min_cost);
// 	if (valid_position(map, x - 1, y) == true && map[y][x - 1].visited == false)
// 		explore_map(map, x - 1, y, cost, min_cost);
// 	if (valid_position(map, x, y - 1) == true && map[y - 1][x].visited == false)
// 		explore_map(map, x, y - 1, cost, min_cost);
// }

// void	explore_map(Map &map, int x, int y, int &cost, int &min_cost)
// {
// 	map[y][x].visited = true;
// 	if (x != 0 || y != 0)
// 		cost += map[y][x].value;
// 	if (cost > min_cost && min_cost_initialized == true)
// 	{
// 		cost -= map[y][x].value;
// 		map[y][x].visited = false;
// 		return;
// 	}
// 	if (map[y][x].visited_once == false)
// 	{
// 		map[y][x].visited_once = true;
// 		map[y][x].distance = cost;
// 	}
// 	else if (cost > map[y][x].distance)
// 	{
// 		cost -= map[y][x].value;
// 		map[y][x].visited = false;
// 		return;
// 	}
// 	else
// 	{
// 		map[y][x].distance = cost;
// 	}
// 	if (end_position(map, x, y) == true)
// 	{
// 		print_map(map);
// 		std::cout << std::endl;
// 		min_cost = cost;
// 		min_cost_initialized = true;
// 		cost -= map[y][x].value;
// 		map[y][x].visited = false;
// 		return;
// 	}
// 	explore_surroundings(map, x, y, cost, min_cost);
// 	cost -= map[y][x].value;
// 	map[y][x].visited = false;
// 	return;
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

int main()
{
	Map	map;
	// int	cost = 0;
	int	min_cost = 0;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
		map.push_back(line_of_points(line));
	// explore_map(map, 0, 0, cost, min_cost);
	min_cost = dijkstra(map);
	std::cout << min_cost << std::endl;
}	