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

void	explore_system(cave_system &cave_system)
{
	cave_system::iterator	start = cave_system.begin();
	while ((*start).first.name.compare("start") != 0)
		start++;
	
}

int main()
{
	cave_system 	cave_system;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
		add_cave_connexion(cave_system, split(line, '-'));

	
	print_system(cave_system);
}	