#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <map>
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

std::vector<std::string> split(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<std::string> result;
	while (getline(ss, tmp, sep))
		result.push_back(tmp);
	return (result);
}

void	print_polymer(std::list<char> &polymer)
{
	for (std::list<char>::iterator it = polymer.begin(); it != polymer.end(); it++)
		std::cout << GREEN << *it << END;
	std::cout << std::endl;
}

void	init_polymer(std::list<char> &polymer, std::string &polymer_string)
{
	for (size_t i = 0; i < polymer_string.size(); i++)
	{
		polymer.push_back(polymer_string[i]);
	}
}

void	process(std::list<char> &polymer, std::map<std::string, char> &rules)
{
	std::string	pair = "  ";
	std::list<char>::iterator first = polymer.begin();
	std::list<char>::iterator second = polymer.begin();
	second++;
	while (1)
	{
		pair[0] = *first;
		pair[1] = *second;
		polymer.insert(second, (*rules.find(pair)).second);
		first = second;
		second++;
		if (second == polymer.end())
			break;
	}
}

std::map<char, int>	count_letters(std::list<char> &polymer)
{
	std::map<char, int> count;
	std::list<char>::iterator end = polymer.end();
	for (std::list<char>::iterator it = polymer.begin(); it != end; it++)
	{
		std::map<char, int>::iterator map_it = count.find(*it);
		if (map_it == count.end())
			count.insert(std::make_pair((*it), 1));
		else
			(*map_it).second++;
	}
	return (count);
}

std::pair<int, int> extract_min_max(std::map<char, int> &count)
{
	std::map<char, int>::iterator it = count.begin();
	int min = (*it).second;
	int max = (*it).second;
	for (; it != count.end(); it++)
	{
		if ((*it).second > max)
			max = (*it).second;
		if ((*it).second < min)
			min = (*it).second;
	}
	return (std::make_pair(min, max));
}

int main()
{
	std::list<char>	polymer;
	std::map<std::string, char> rules;
	std::string		line;
	std::ifstream	input("input.txt");
	std::getline(input, line);
	init_polymer(polymer, line);
	std::getline(input, line);
	while (std::getline(input, line))
	{
		std::vector<std::string> result = split(line, ' ');
		rules.insert(std::make_pair(result[0], result[2][0]));
	}
	for (int i = 0; i < 10; i++)
	{
		// print_polymer(polymer);
		process(polymer, rules);
	}
	std::map<char, int> count = count_letters(polymer);
	std::pair<int, int> result = extract_min_max(count);
	std::cout << result.second - result.first << std::endl;
}	