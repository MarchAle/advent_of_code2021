#include <fstream>
#include <iostream>
#include <set>

int main()
{
	int previous_depth = 0;
	int current_depth = 0;
	int increase_count = 0;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
	{
		current_depth = std::stoi(line);
		if (current_depth > previous_depth && previous_depth != 0)
			increase_count++;
		previous_depth = current_depth;
	}
	std::cout << increase_count << std::endl;
}