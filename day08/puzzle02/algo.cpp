#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>

typedef	struct s_connection
{
	char	segment;
	char	wire;
}	t_connection;

std::vector<std::string> split(std::string &line, char sep)
{
	std::string tmp = line;
	std::stringstream ss(line);
	std::vector<std::string> result;
	while (getline(ss, tmp, sep))
	{
		if (tmp.length())
			result.push_back(tmp);
	}
	return (result);
}

void	init_connections(std::list<t_connection> &connections)
{
	char	segment = 'a';
	std::list<t_connection>::iterator end = connections.end();
	for (std::list<t_connection>::iterator it = connections.begin(); it != end; it++)
		(*it).segment = segment++;
}

std::list<t_connection>::iterator	connections_segment(std::list<t_connection> &connections, char segment)
{
	std::list<t_connection>::iterator end = connections.end();
	for (std::list<t_connection>::iterator it = connections.begin(); it != end; it++)
	{
		if ((*it).segment == segment)
			return (it);
	}
	return (connections.end());
}

void	find_segments_by_wire_occurence(std::list<t_connection> &connections, std::vector<std::string> &input_digits)
{
	std::vector<int> wire_occurence(7, 0);
	std::vector<std::string>::iterator end = input_digits.end();
	for (std::vector<std::string>::iterator it = input_digits.begin(); it != end; it++)
	{
		for (size_t i = 0; i < (*it).length(); i++)
			wire_occurence[(*it)[i] - 97]++;
	}
	for (int i = 0; i < 7; i++)
	{
		switch (wire_occurence[i])
		{
			case 4:
				(*connections_segment(connections, 'e')).wire = i + 97;
				break;
			case 6:
				(*connections_segment(connections, 'b')).wire = i + 97;
				break;
			case 8:
				if ((*connections_segment(connections, 'a')).wire != i + 97)
					(*connections_segment(connections, 'c')).wire = i + 97;
				break;
			case 9:
				(*connections_segment(connections, 'f')).wire = i + 97;
				break;
			
			default:
				break;
		}
	}
}

void	find_segments_a(std::list<t_connection> &connections, std::vector<std::string> &input_digits)
{
	std::string two_char;
	std::string three_char;
	std::vector<std::string>::iterator end = input_digits.end();
	for (std::vector<std::string>::iterator it = input_digits.begin(); it != end; it++)
	{
		if ((*it).length() == 2)
			two_char = *it;
		if ((*it).length() == 3)
			three_char = *it;
	}
	for (int i = 0; i < 3; i++)
	{
		int find = 0;
		for (int j = 0; j < 2; j++)
		{
			if (three_char[i] == two_char[j])
				find = 1;
		}
		if (!find)
			(*connections_segment(connections, 'a')).wire = three_char[i];
	}
}

void	find_connections(std::list<t_connection> &connections, std::vector<std::string> &input_digits, std::vector<std::string> &signals)
{
	find_segments_a(connections, input_digits);
	find_segments_by_wire_occurence(connections, input_digits);
	std::vector<std::string>::iterator end = input_digits.end();
	for (std::vector<std::string>::iterator it = input_digits.begin(); it != end; it++)
	{
		switch ((*it).length())
		{
			case 2:
				if ((*it)[0] != (*connections_segment(connections, 'f')).wire)
					(*connections_segment(connections, 'c')).wire = (*it)[0];
				else
					(*connections_segment(connections, 'c')).wire = (*it)[1];
				signals[1] = (*it);
				break;

			case 3:
				signals[7] = (*it);
				break;

			case 7:
				signals[8] = (*it);
				break;

			default:
				break;
		}
	}
	for (std::vector<std::string>::iterator it = input_digits.begin(); it != end; it++)
	{
		switch ((*it).length())
		{
			case 4:
				for (int i = 0; i < 4; i++)
				{
					if ((*it)[i] == (*connections_segment(connections, 'b')).wire ||
						(*it)[i] == (*connections_segment(connections, 'c')).wire ||
						(*it)[i] == (*connections_segment(connections, 'f')).wire)
						continue ;
					(*connections_segment(connections, 'd')).wire = (*it)[i];
				}
				signals[4] = (*it);
				break;

			default:
				break;
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (i + 97 != (*connections_segment(connections, 'a')).wire &&
			i + 97 != (*connections_segment(connections, 'b')).wire &&
			i + 97 != (*connections_segment(connections, 'c')).wire &&
			i + 97 != (*connections_segment(connections, 'd')).wire &&
			i + 97 != (*connections_segment(connections, 'e')).wire &&
			i + 97 != (*connections_segment(connections, 'f')).wire)
			(*connections_segment(connections, 'g')).wire = i + 97;
	}
}

void	find_signals(std::list<t_connection> &connections, std::vector<std::string> &input_digits, std::vector<std::string> &signals)
{
	std::vector<std::string>::iterator end = input_digits.end();
	for (std::vector<std::string>::iterator it = input_digits.begin(); it != end; it++)
	{
		if ((*it).length() == 5)
		{
			int is_three = 1;
			for (int  i = 0; i < 5; i++)
			{
				if ((*it)[i] == (*connections_segment(connections, 'b')).wire)
				{
					signals[5] = *it;
					is_three = 0;
					break;
				}
				if ((*it)[i] == (*connections_segment(connections, 'e')).wire)
				{
					signals[2] = *it;
					is_three = 0;
					break;
				}
			}
			if (is_three)
				signals[3] = *it;
		}
		if ((*it).length() == 6)
		{
			int c_is_missing = 1, d_is_missing = 1, e_is_missing = 1; 
			for (int i = 0; i < 6; i++)
			{
				if ((*it)[i] == (*connections_segment(connections, 'c')).wire)
					c_is_missing = 0;
				if ((*it)[i] == (*connections_segment(connections, 'd')).wire)
					d_is_missing = 0;
				if ((*it)[i] == (*connections_segment(connections, 'e')).wire)
					e_is_missing = 0;
			}
			if (c_is_missing)
				signals[6] = *it;
			if (d_is_missing)
				signals[0] = *it;
			if (e_is_missing)
				signals[9] = *it;
		}
	}
}

std::string sortString(const std::string& inputString) {
    std::string sortedString = inputString;
    std::sort(sortedString.begin(), sortedString.end());
    return sortedString;
}

char	digit_from_signal(std::string &signal, std::vector<std::string> &signals)
{
	for (size_t i = 0; i < signals.size(); i++)
	{
		if ((sortString(signals[i])).compare(sortString(signal)) == 0)
			return (i + 48);
	}
	return ('*');
}

int main()
{
	std::vector<std::string> input_digits;
	std::vector<std::string> output_digits;
	std::string		line;
	std::ifstream	input("input.txt");
	int sum = 0;
	while (std::getline(input, line))
	{
		std::list<t_connection>	connections(7);
		std::vector<std::string> signals(10);
		init_connections(connections);
		input_digits = split(split(line, '|')[0], ' ');
		find_connections(connections, input_digits, signals);
		find_signals(connections, input_digits, signals);
		output_digits = split(split(line, '|')[1], ' ');
		char output_str[4];
		for (size_t i = 0; i < output_digits.size(); i++)
			output_str[i] = digit_from_signal(output_digits[i], signals);
		sum += std::stoi(output_str);
	}
	std::cout << "sum : " << sum << std::endl;
}