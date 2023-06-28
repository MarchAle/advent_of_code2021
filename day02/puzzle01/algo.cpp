#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>

std::vector<std::string> split(std::string &names)
{
	std::string tmp = names;
	std::stringstream ss(names);
	std::vector<std::string> result;
	while (getline(ss, tmp, ' '))
		result.push_back(tmp);
	return (result);
}

int main()
{
	std::vector<std::string> cmd;
	int horizontal_pos = 0;
	int depth = 0;

	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
	{
		cmd = split(line);
		int value = std::stoi(cmd[1]);
		if (cmd[0].compare("forward") == 0)
			horizontal_pos += value;
		else if (cmd[0].compare("down") == 0)
			depth += value;
		else if (cmd[0].compare("up") == 0)
			depth -= value;
	}
	std::cout << horizontal_pos * depth << std::endl;
}