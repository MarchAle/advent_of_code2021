#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>
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

#define PARENTHESIS 1
#define CURLY_BRACKET 2
#define SQUARE_BRACKET 3
#define ANGLE_BRACKET 4

int	close_chunck(std::stack<int> &sequence, int closing_char)
{
	if (sequence.top() != closing_char)
		return (closing_char);
	sequence.pop();
	return (0);
}

int parse_line(std::string &line)
{
	std::stack<int>	sequence;
	int return_value;

	for (size_t i = 0; i < line.length(); i++)
	{
		return_value = 0;
		switch (line[i])
		{
			case '(':
				sequence.push(PARENTHESIS);
				break;
			case '[':
				sequence.push(SQUARE_BRACKET);
				break;
			case '{':
				sequence.push(CURLY_BRACKET);
				break;
			case '<':
				sequence.push(ANGLE_BRACKET);
				break;
			case ')':
				return_value = close_chunck(sequence, PARENTHESIS);
				break;
			case ']':
				return_value = close_chunck(sequence, SQUARE_BRACKET);
				break;
			case '}':
				return_value = close_chunck(sequence, CURLY_BRACKET);
				break;
			case '>':
				return_value = close_chunck(sequence, ANGLE_BRACKET);
				break;
			
			default:
				break;
		}
		if (return_value == PARENTHESIS)
			return (3);
		if (return_value == SQUARE_BRACKET)
			return (57);
		if (return_value == CURLY_BRACKET)
			return (1197);
		if (return_value == ANGLE_BRACKET)
			return (25137);
	}
	return (0);
}

int main()
{
	int	sum = 0;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
		sum += parse_line(line);
	std::cout << sum << std::endl;
}