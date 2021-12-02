#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

std::vector<unsigned int> GetDepthsFromInput();
unsigned int Part1Comparison();
unsigned int Part2Comparison();

main()
{
	std::cout << Part1Comparison() << ", " << Part2Comparison() << '\n';
}

/// <summary>
/// Loads data from formatted input text file
/// </summary>
/// <returns> Vector collection of input text as uint32 </returns>
std::vector<unsigned int> GetDepthsFromInput()
{
	//open file
	std::ifstream file("input.txt", std::ios::in);
	
	//generate collection to contain inputs
	std::vector<unsigned int> inputs;
	
	//iterate over each line and pump, as int, into collection. Does not account for flying submarines
	for(std::string line; std::getline(file, line);)
		inputs.push_back(std::stoi(line));
	
	return inputs;
}

/// <summary>
/// Performs the 'part 1' operation
/// </summary>
/// <returns> Quantity of depth increases of input instructions </returns>
unsigned int Part1Comparison()
{	
	//get input file values
	std::vector<unsigned int> depths = GetDepthsFromInput();
	
	//counter of terrain depth increments
	unsigned int deepenings = 0;
	
	//increment sea floor depthenings
	for(int ind = 1; ind < depths.size(); ind++)
		if (depths[ind] > depths[ind-1])
			deepenings++;
		
	return deepenings;
}

/// <summary>
/// Performs the 'part 2' operation
/// </summary>
/// <returns> Quantity of depth increases of input instructions, using three consecutive values as samples </returns>
unsigned int Part2Comparison()
{	
	//get input file values
	std::vector<unsigned int> depths = GetDepthsFromInput();
	
	//count of terrain deepenings and sampler of terrain surface
	unsigned int 
		deepenings = 0,
		sample = depths[0] + depths[1] + depths[2];
	
	//incrementor of terrain deepenings, smooved over 3-part sample
	for(int ind = 3; ind < depths.size(); ind++)
	{
		if (depths[ind - 2] + depths[ind - 1] + depths[ind] > sample)
			deepenings++;
		sample = depths[ind - 2] + depths[ind - 1] + depths[ind];
	}

	return deepenings;
}

