#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// enum for directions
enum Directions{ FORWARD = 'f', DOWN = 'd', UP = 'u' };

// declarations
std::vector<std::pair<unsigned char, unsigned int>> GetDirectionsFromInput();
void PositionFromDirections(unsigned int& distance, unsigned int& depth, const std::vector<std::pair<unsigned char, unsigned int>>& directions);

main()
{
	// get instruction pairs
	std::vector<std::pair<unsigned char, unsigned int>> directions = GetDirectionsFromInput();
	// declare values
	unsigned int distance = 0, depth = 0;
	// process values from input pairs
	PositionFromDirections(distance, depth, directions);
	// output values
	std::cout << "Traveled: " << distance << ", at a depth of: " << depth << ", for some reason totalling: " << distance * depth << '\n'; 
}

/// <summary>
/// Generate collection of pairs from input text file
/// </summary>
/// <returns> Collection of instruction pairs </returns>
std::vector<std::pair<unsigned char, unsigned int>> GetDirectionsFromInput()
{
	// open input file
	std::ifstream file("input.txt", std::ios::in);
	// generate vector collection of input pairs
	std::vector<std::pair<unsigned char, unsigned int>> inputs = std::vector<std::pair<unsigned char, unsigned int>>();
	
	// generate pairs from each line of input file
	for(std::string line; std::getline(file, line);)
	{
		int carett = line.find(' ');
		inputs.push_back(std::make_pair(line.at(0), std::stoi(line.substr(carett + 1))));
	}
	
	return inputs;
}

/// <summary>
/// Calculate horizontal range and descent depth from adjusted pitch, using *really* inaccurate math 
/// </summary>
/// <param name="distance"> distance reference </param>
/// <param name="depth"> depth reference </param>
/// <param name="directions"> the diving instructions </param>
void PositionFromDirections(unsigned int& distance, unsigned int& depth, const std::vector<std::pair<unsigned char, unsigned int>>& directions)
{
	// submarine trim, "aim" is not a thing related to rotation
	int trim=0;

	//iterate instructions and process as necessary
	for(std::pair<unsigned char, unsigned int> direction : directions)
		switch (direction.first)
		{
			case FORWARD:
				distance += direction.second;
				depth += direction.second * trim;
				break;
			case UP:
				trim -= direction.second;
				break;
			case DOWN:
				trim += direction.second;
				break;
		}
}