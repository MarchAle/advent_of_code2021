#include <fstream>
#include <iostream>
#include <set>

int main()
{
	int nb_measurement = 0;
	int current_depth = 0;
	int set_one = 0;
	int set_two = 0;
	int set_three = 0;
	int increase_count = 0;
	std::string		line;
	std::ifstream	input("input.txt");
	while (std::getline(input, line))
	{
		nb_measurement++;
		current_depth = std::stoi(line);
		if (nb_measurement < 4)
		{
			switch (nb_measurement % 3)
			{
			case 1:
				set_one += current_depth;
				break;
			case 2:
				set_one += current_depth;
				set_two += current_depth;
				break;
			case 3:
				set_one += current_depth;
				set_two += current_depth;
				set_three += current_depth;
				break;
			
			default:
				break;
			}
		}
		else
		{
			switch (nb_measurement % 3)
			{
				case 1:
					set_two += current_depth;
					set_three += current_depth;
					if (set_two > set_one)
						increase_count++;
					set_one = current_depth;
					break;
				case 2:
					set_three += current_depth;
					set_one += current_depth;
					if (set_three > set_two)
						increase_count++;
					set_two = current_depth;
					break;
				case 0:
					set_one += current_depth;
					set_two += current_depth;
					if (set_one > set_three)
						increase_count++;
					set_three = current_depth;
					break;
				
				default:
					break;
			}
		}
	}
	std::cout << increase_count << std::endl;
}