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

typedef	struct s_coord
{
	int x;
	int y;
} t_coord;


std::vector<std::string> split(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<std::string> result;
	while (getline(ss, tmp, sep))
		result.push_back(tmp);
	return (result);
}

void	add_point(std::vector<t_coord> &points, std::vector<std::string> &result)
{
	t_coord coord;
	
	coord.x = std::stoi(result[0]);
	coord.y = std::stoi(result[1]);
	points.push_back(coord);
}

void	add_instruction(std::vector<std::pair<int, int> > &instructions, std::vector<std::string> result)
{
	instructions.push_back(std::make_pair((result[0][0]), std::stoi(result[1])));
}

void	fold_x(std::vector<t_coord> &points, int &line)
{
	std::vector<t_coord>::iterator end = points.end();
	for (std::vector<t_coord>::iterator it = points.begin(); it != end; it++)
	{
		if ((*it).x > line)
			(*it).x = 2 * line - (*it).x;
	}
}

void	fold_y(std::vector<t_coord> &points, int &line)
{
	std::vector<t_coord>::iterator end = points.end();
	for (std::vector<t_coord>::iterator it = points.begin(); it != end; it++)
	{
		if ((*it).y > line)
			(*it).y = 2 * line - (*it).y;
	}
}

std::pair<int, int>	get_sheet_size(std::vector<t_coord> &points)
{
	int x_max = 0;
	int y_max = 0;
	std::vector<t_coord>::iterator end = points.end();
	for (std::vector<t_coord>::iterator it = points.begin(); it != end; it++)
	{
		if ((*it).x > x_max)
			x_max = (*it).x;
		if ((*it).y > y_max)
			y_max = (*it).y;
	}
	return (std::make_pair(x_max + 1, y_max + 1));
}

void	draw_sheet(std::vector<std::vector<char> > &sheet, std::vector<t_coord> &points)
{
	std::vector<t_coord>::iterator end = points.end();
	for (std::vector<t_coord>::iterator it = points.begin(); it != end; it++)
		sheet[(*it).y][(*it).x] = '#';
}

int		count_dots(std::vector<std::vector<char> > &sheet)
{
	int count = 0;

	std::vector<std::vector<char> >::iterator end = sheet.end();
	for (std::vector<std::vector<char> >::iterator it = sheet.begin(); it != end; it++)
	{
		std::vector<char>::iterator line_end = (*it).end();
		for (std::vector<char>::iterator line_it = (*it).begin(); line_it != line_end; line_it++)
		{
			if (*(line_it) == '#')
				count++;
		}
	}
	return (count);
}

int main()
{
	std::vector<t_coord> points;
	std::vector<std::pair<int, int> > instructions;
	std::pair<int, int>	sheet_size;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
	{
		std::vector<std::string> result = split(line, ',');
		if (result.size() == 2)
			add_point(points, result);
		if (result.size() == 1)
			add_instruction(instructions, split(split(line, ' ')[2], '='));
	}
	std::vector<std::pair<int, int> >::iterator end = instructions.end();
	for (std::vector<std::pair<int, int> >::iterator it = instructions.begin(); it != end; it++)
	{
		if ((*it).first == 'x')
			fold_x(points, (*it).second);
		else if ((*it).first == 'y')
			fold_y(points, (*it).second);
		break;
	}
	sheet_size = get_sheet_size(points);
	std::vector<char> sheet_line(sheet_size.first, '.');
	std::vector<std::vector<char> > sheet(sheet_size.second, sheet_line);
	draw_sheet(sheet, points);
	std::cout << count_dots(sheet) << std::endl;
}	