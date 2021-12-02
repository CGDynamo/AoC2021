#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//
enum Directions{ FORWARD = 'f', DOWN = 'd', UP = 'u' };

std::vector<std::pair<unsigned char, unsigned int>> GetDirectionsFromInput();

void PositionFromDirections(unsigned int& distance, unsigned int& depth, const std::vector<std::pair<unsigned char, unsigned int>>& directions);

main()
{
	std::vector<std::pair<unsigned char, unsigned int>> directions = GetDirectionsFromInput();
	unsigned int distance = 0, depth = 0;
	PositionFromDirections(distance, depth, directions);
	std::cout << "Traveled: " << distance << ", at a depth of: " << depth << ", for some reason totalling: " << distance * depth << '\n'; 
}

std::vector<std::pair<unsigned char, unsigned int>> GetDirectionsFromInput()
{
	std::ifstream file("input.txt", std::ios::in);
	std::vector<std::pair<unsigned char, unsigned int>> inputs = std::vector<std::pair<unsigned char, unsigned int>>();
	
	for(std::string line; std::getline(file, line);)
	{
		int carett = line.find(' ');
		inputs.push_back(std::make_pair(line.at(0), std::stoi(line.substr( carett+1))));
	}
	
	return inputs;
}

void PositionFromDirections(unsigned int& distance, unsigned int& depth, const std::vector<std::pair<unsigned char, unsigned int>>& directions)
{
	int trim=0;
	for(std::pair<unsigned char, unsigned int> direction : directions)
		switch (direction.first)
		{
			case 'f':
				distance += direction.second;
				depth += direction.second * trim;
				break;
			case 'u':
				trim -= direction.second;
				break;
			case 'd':
				trim += direction.second;
				break;
		}
}