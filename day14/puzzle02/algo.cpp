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

void	print_count(std::map<char, unsigned long> &count)
{
	for (std::map<char, unsigned long>::iterator it = count.begin(); it != count.end(); it++)
	{
		std::cout << GREEN << (*it).first << " " << BLUE << (*it).second << END << std::endl;
	}
}

void	init_polymer(std::map<std::string, unsigned long> &polymer, std::string &polymer_string)
{
	std::string	pair = "  ";
	for (size_t i = 0; i < polymer_string.size() - 1; i++)
	{
		pair[0] = polymer_string[i];
		pair[1] = polymer_string[i + 1];
		(*polymer.find(pair)).second++;
	}
}

std::map<std::string, unsigned long>	process(std::map<std::string, unsigned long> &polymer, std::map<std::string, std::pair<std::string, std::string> > &rules, std::map<std::string, unsigned long> &empty_pair_count, std::map<char, unsigned long> &count)
{
	std::map<std::string, unsigned long> new_polymer = empty_pair_count;
	for (std::map<std::string, unsigned long>::iterator it = polymer.begin(); it != polymer.end(); it++)
	{
		std::pair<std::string, std::string> resulting_pair = (*rules.find((*it).first)).second;
		(*new_polymer.find(resulting_pair.first)).second += (*it).second;
		(*new_polymer.find(resulting_pair.second)).second += (*it).second;
		std::map<char, unsigned long>::iterator map_it = count.find(resulting_pair.first[1]);
		if (map_it == count.end())
			count.insert(std::make_pair(resulting_pair.first[1], (*it).second));
		else
			(*map_it).second += (*it).second;
	}
	return (new_polymer);
}

std::pair<unsigned long, unsigned long> extract_min_max(std::map<char, unsigned long> &count)
{
	std::map<char, unsigned long>::iterator it = count.begin();
	unsigned long min = (*it).second;
	unsigned long max = (*it).second;
	for (; it != count.end(); it++)
	{
		if ((*it).second > max)
			max = (*it).second;
		if ((*it).second < min)
			min = (*it).second;
	}
	return (std::make_pair(min, max));
}

std::pair<std::string, std::string> make_rule(std::string &base_pair, char &inserted_letter)
{
	std::string	pair_one = "  ";
	std::string	pair_two = "  ";
	pair_one[0] = base_pair[0];
	pair_one[1] = pair_two[0] = inserted_letter;
	pair_two[1] = base_pair[1];
	return (std::make_pair(pair_one, pair_two));
}

void init_count(std::map<char, unsigned long> &count, std::string &polymer_str)
{
	for (size_t i = 0; i < polymer_str.size(); i++)
	{
		std::map<char, unsigned long>::iterator map_it = count.find(polymer_str[i]);
		if (map_it == count.end())
			count.insert(std::make_pair(polymer_str[i], 1));
		else
			(*map_it).second++;
	}
}

int main()
{
	std::string	polymer_str;
	std::map<std::string, std::pair<std::string, std::string> > rules;
	std::map<std::string, unsigned long> empty_pair_count;
	std::map<std::string, unsigned long> polymer;
	std::map<char, unsigned long> count;
	std::string		line;
	std::ifstream	input("input.txt");
	std::getline(input, polymer_str);
	std::getline(input, line);
	while (std::getline(input, line))
	{
		std::vector<std::string> result = split(line, ' ');
		rules.insert(std::make_pair(result[0], make_rule(result[0], result[2][0])));
		empty_pair_count.insert(std::make_pair(result[0], 0));
	}
	polymer = empty_pair_count;
	init_count(count, polymer_str);
	init_polymer(polymer, polymer_str);
	for (int i = 0; i < 40; i++)
	{
		polymer = process(polymer, rules, empty_pair_count, count);
	}
	// print_count(count);
	std::pair<unsigned long, unsigned long> result = extract_min_max(count);
	std::cout << result.second - result.first << std::endl;
}	