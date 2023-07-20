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

typedef struct s_cave
{
	std::string name;
	int			visited;
}	t_cave;

typedef std::pair<t_cave, std::vector<std::string> > cave;
typedef std::vector<cave> cave_system;
typedef std::vector<std::vector<std::string> > paths;

std::pair<std::string, std::string> split(std::string &line, char sep)
{
	std::pair<std::string, std::string> new_pair;
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<std::string> result;
	getline(ss, tmp, sep);
	new_pair.first = tmp;
	getline(ss, tmp, sep);
	new_pair.second = tmp;
	return (new_pair);
}

std::pair<int, cave_system::iterator> is_cave_listed(cave_system &cave_system, std::string &cave_name)
{
	cave_system::iterator it = cave_system.begin();
	cave_system::iterator end = cave_system.end();
	for (; it != end; it++)
	{
		if ((*it).first.name.compare(cave_name) == 0)
			return (std::make_pair(1, it));
	}
	return (std::make_pair(0, it));
}

void	add_cave_connexion(cave_system &cave_system, std::pair<std::string, std::string> connexion)
{
	std::string first_cave_name = connexion.first;
	std::string second_cave_name = connexion.second;
	for (int i = 0; i < 2; i++)
	{
		std::pair<int, cave_system::iterator> cave_info = is_cave_listed(cave_system, first_cave_name);
		if (cave_info.first == 1)
			(*cave_info.second).second.push_back(second_cave_name);
		else
		{
			std::vector<std::string> connexion_list(1, second_cave_name);
			t_cave	new_cave;
			new_cave.name = first_cave_name;
			new_cave.visited = 0;
			cave_system.push_back(std::make_pair(new_cave, connexion_list));
		}
		first_cave_name = connexion.second;
		second_cave_name = connexion.first;
	}
}

void 	print_system(cave_system &system)
{
	for (size_t i = 0; i < system.size(); i++)
	{
		std::cout << system[i].first.name << " : ";
		for (size_t j = 0; j < system[i].second.size(); j++)
			std::cout << system[i].second[j] << " ";
		std::cout << std::endl;
	}
}

bool	already_visited(cave_system &cave_system, std::string &name)
{
	cave_system::iterator end = cave_system.end();
	for (cave_system::iterator it = cave_system.begin(); it != end; it++)
	{
		if ((*it).first.name.compare(name) == 0 && (*it).first.visited == 1)
			return (true);
	}
	return (false);
}

bool	is_small_cave(std::string &name)
{
	if (islower(name[0]))
		return (true);
	return (false);
}

void	set_as_visited(cave_system &cave_system, std::string &name)
{
	cave_system::iterator end = cave_system.end();
	for (cave_system::iterator it = cave_system.begin(); it != end; it++)
	{
		if ((*it).first.name.compare(name) == 0 && is_small_cave(name))
			(*it).first.visited = 1;
	}
}

void	set_as_not_visited(cave_system &cave_system, std::string &name)
{
	cave_system::iterator end = cave_system.end();
	for (cave_system::iterator it = cave_system.begin(); it != end; it++)
	{
		if ((*it).first.name.compare(name) == 0 && (*it).first.name.compare("start") != 0)
			(*it).first.visited = 0;
	}
}

cave_system::iterator	get_node(cave_system &cave_system, std::string &name)
{
	cave_system::iterator end = cave_system.end();
	for (cave_system::iterator it = cave_system.begin(); it != end; it++)
	{
		if ((*it).first.name.compare(name) == 0)
			return (it);
	}
	return (cave_system.end());
}

void	explore_system(cave_system::iterator &node, cave_system &cave_system, paths &paths, std::vector<std::string> &current_path)
{
	if ((*node).first.name.compare("end") == 0)
	{
		paths.push_back(current_path);
		current_path.pop_back();
		return;
	}
	for (std::vector<std::string>::iterator it = (*node).second.begin(); it != (*node).second.end(); it++)
	{
		if (!already_visited(cave_system, *it))
		{
			set_as_visited(cave_system, *it);
			current_path.push_back(*it);
			cave_system::iterator next_node = get_node(cave_system, *it);
			explore_system(next_node, cave_system, paths, current_path);
			set_as_not_visited(cave_system, *it);
		}
	}
	current_path.pop_back();
	return;
}

void	print_paths(paths &paths)
{
	for (paths::iterator it = paths.begin(); it != paths.end(); it++)
	{
		for (std::vector<std::string>::iterator cave_it = (*it).begin(); cave_it != (*it).end(); cave_it++)
		{
			std::cout << *cave_it << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	cave_system 	cave_system;
	paths			paths;
	std::vector<std::string> current_path;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
		add_cave_connexion(cave_system, split(line, '-'));

	cave_system::iterator	start = cave_system.begin();
	while ((*start).first.name.compare("start") != 0)
		start++;
	(*start).first.visited = 1;
	current_path.push_back((*start).first.name);
	// print_system(cave_system);
	// std::cout << std::endl;
	explore_system(start, cave_system, paths, current_path);
	
	// print_paths(paths);
	std::cout << paths.size() << std::endl;
}	