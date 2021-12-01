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

std::vector<unsigned int> GetDepthsFromInput()
{
	std::ifstream file("input.txt", std::ios::in);
	
	std::vector<unsigned int> inputs;
	
	for(std::string line; std::getline(file, line);)
		inputs.push_back(std::stoi(line));
	
	return inputs;
}

unsigned int Part1Comparison()
{	
	std::vector<unsigned int> depths = GetDepthsFromInput();
	
	unsigned int deepenings = 0;
	
	for(int ind = 1; ind < depths.size(); ind++)
		if (depths[ind] > depths[ind-1])
			deepenings++;
		
	return deepenings;
}

unsigned int Part2Comparison()
{	
	std::vector<unsigned int> depths = GetDepthsFromInput();
	
	unsigned int 
		deepenings = 0,
		sample = depths[0] + depths[1] + depths[2];
	
	for(int ind = 3; ind < depths.size(); ind++)
	{
		if (depths[ind - 2] + depths[ind - 1] + depths[ind] > sample)
			deepenings++;
		sample = depths[ind - 2] + depths[ind - 1] + depths[ind];
	}
	return deepenings;
}

