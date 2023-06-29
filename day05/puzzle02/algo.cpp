#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<int> > Grid;
typedef struct s_coord
{
	int x;
	int y;
}	t_coord;


std::vector<std::string> split(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<std::string> result;
	while (getline(ss, tmp, sep))
		result.push_back(tmp);
	return (result);
}

void	init_grid(Grid &grid)
{
	std::vector<int> line;
	for (int i = 0; i < 1000; i++)
		line.push_back(0);
	for (int i = 0; i < 1000; i++)
		grid.push_back(line);
}

t_coord	getCoord(std::string &coord_string)
{
	t_coord new_coord;
	std::vector<std::string> split_coord = split(coord_string, ',');

	new_coord.x = std::stoi(split_coord[0]);
	new_coord.y = std::stoi(split_coord[1]);

	return (new_coord);
}

void	draw_vertical(Grid &grid, t_coord &start, t_coord &end)
{
	int direction = start.y < end.y ? 1 : -1;
	for (int i = start.y; i != end.y + direction; i += direction)
		grid[i][start.x]++;
}

void	draw_horizontal(Grid &grid, t_coord &start, t_coord &end)
{
	int direction = start.x < end.x ? 1 : -1;
	for (int i = start.x; i != end.x + direction; i += direction)
		grid[start.y][i]++;
}

void	draw_diagonal(Grid &grid, t_coord &start, t_coord &end)
{
	int direction_x = start.x < end.x ? 1 : -1;
	int direction_y = start.y < end.y ? 1 : -1;
	int start_y = start.y;

	for (int i = start.x; i != end.x + direction_x; i += direction_x)
	{
		grid[start_y][i]++;
		start_y += direction_y;
	}
}

void	scan_grid(Grid &grid)
{
	int count = 0;
	Grid::iterator row_end = grid.end();
	for (Grid::iterator row_it = grid.begin(); row_it != row_end; row_it++)
	{
		std::vector<int>::iterator line_end = (*row_it).end();
		for (std::vector<int>::iterator line_it = (*row_it).begin(); line_it != line_end; line_it++)
		{
			// std::cout << *line_it << " ";
			if (*line_it >= 2)
				count++;
		}
		// std::cout << std::endl;
	}
	std::cout << "Points where at least two lines overlap : " << count << std::endl;
}

int main()
{
	std::string		line;
	std::ifstream	input("input.txt");
	Grid grid;
	t_coord start, end;

	init_grid(grid);

	while (std::getline(input, line))
	{
		std::vector<std::string> split_line = split(line, ' ');
		start = getCoord(split_line[0]);
		end = getCoord(split_line[2]);

		if (start.x == end.x)
			draw_vertical(grid, start, end);
		else if (start.y == end.y)
			draw_horizontal(grid, start, end);
		else
			draw_diagonal(grid, start, end);
	}
	scan_grid(grid);
}