#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <list>
#include <cmath>
#include <bitset>
#include <string>

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

int version_sum = 0;

std::string hextobin(const std::string &s)
{
    std::string out;
    for(size_t i = 0; i < s.length(); i++){
        int n;
        if(s[i] <= '9' and s[i] >= '0')
            n = s[i] - '0';
        else
            n = 10 + s[i] - 'A';
        for(int j = 3; j >= 0; j--)
		{
            out.push_back((n & (1 << j))? '1':'0');
		}
    }
    return (out);
}

unsigned long bintodec(const std::string &s)
{
	std::bitset<64> bitset;
	int pos = 0;
	for (int i = s.length() - 1; i >= 0; i--)
		bitset.set(pos++, s[i] != '0');
    return (bitset.to_ulong());
}

int		bits_convert(std::string *packet, size_t &position, int size)
{
	std::string	bit_buffer;
	for (int j = 0; j < size; j++)
	{
		bit_buffer.push_back((*packet)[position]);
		position++;
	}
	return (bintodec(bit_buffer));
}

long		get_literal_value(std::string *packet, size_t &position)
{
	std::string bit_buffer;
	bool		stop = false;
	while (stop == false)
	{
		if ((*packet)[position++] == '0')
			stop = true;
		for (int j = 0; j < 4; j++)
			bit_buffer.push_back((*packet)[position + j]);
		position += 4;
	}
	return (bintodec(bit_buffer));
}

long	sum(std::vector<long> &values)
{
	long sum = 0;
	for (size_t i = 0; i < values.size(); i++)
		sum += values[i];
	return (sum);
}

long	product(std::vector<long> &values)
{
	long product = values[0];
	if (values.size() == 1)
		return (product);
	for (size_t i = 1; i < values.size(); i++)
		product *= values[i];
	return (product);
}

long	min(std::vector<long> &values)
{
	long min = values[0];
	for (size_t i = 1; i < values.size(); i++)
	{
		if (values[i] < min)
			min = values[i];
	}
	return (min);
}

long	max(std::vector<long> &values)
{
	long max = values[0];
	for (size_t i = 1; i < values.size(); i++)
	{
		if (values[i] > max)
			max = values[i];
	}
	return (max);
}

long	greater(std::vector<long> &values)
{
	return (values[0] > values[1] ? 1 : 0);
}

long	less(std::vector<long> &values)
{
	return (values[0] < values[1] ? 1 : 0);
}

long	equal(std::vector<long> &values)
{
	return (values[0] == values[1] ? 1 : 0);
}

std::vector<long> execute(std::vector<long> &values, int type)
{
	std::vector<long> result;
	switch (type)
	{
		case 0:
			result.push_back(sum(values));
			break;
		case 1:
			result.push_back(product(values));
			break;
		case 2:
			result.push_back(min(values));
			break;
		case 3:
			result.push_back(max(values));
			break;
		case 4:
			return (values);
		case 5:
			result.push_back(greater(values));
			break;
		case 6:
			result.push_back(less(values));
			break;
		case 7:
			result.push_back(equal(values));
			break;
		
		default:
			break;
	}
	return (result);
}

std::vector<long>	parse_packet(std::string *packet, size_t &pos)
{
	int version;
	int type_id;
	long	literal_value;
	int	subpacket_length;
	int	nb_of_subpackets;
	std::vector<long> values;

	version = bits_convert(packet, pos, 3);
	type_id = bits_convert(packet, pos, 3);
	version_sum += version;
	if (type_id == 4)
	{
		literal_value = get_literal_value(packet, pos);
		values.push_back(literal_value);
	}
	else
	{
		if ((*packet)[pos] == '0')
		{
			subpacket_length = bits_convert(packet, ++pos, 15);
			size_t start_pos = pos;
			while (pos < start_pos + subpacket_length)
			{
				std::vector<long> tmp_vector = parse_packet(packet, pos);
				values.insert(values.end(), tmp_vector.begin(), tmp_vector.end());
			}
		}
		else if ((*packet)[pos] == '1')
		{
			nb_of_subpackets = bits_convert(packet, ++pos, 11);
			for (int i = 0; i < nb_of_subpackets; i++)
			{
				std::vector<long> tmp_vector = parse_packet(packet, pos);
				values.insert(values.end(), tmp_vector.begin(), tmp_vector.end());
			}
		}
	}
	return (execute(values, type_id));
}

int main()
{
	std::string		line;
	std::string		packet;
	std::ifstream	input("input.txt");
	std::getline(input, line);
	packet = hextobin(line);
	size_t pos = 0;
	std::vector<long> result = parse_packet(&packet, pos);

	std::cout << BGREEN << "version_sum : " << version_sum << std::endl;
	std::cout << BCYAN << "result : " << result[0] << std::endl;;
}