#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> GetInputValues();
void ProcessPart1(unsigned int& gamme, unsigned int& epsilon, const std::vector<std::string>& values);
void ProcessPart2(unsigned int& oxy, unsigned int& co2, const std::vector<std::string>& values);

main()
{
	std::vector<std::string> values = GetInputValues();
	
	unsigned int gamma = 0, epsilon = 0, oxy = 0, co2 = 0;
	
	ProcessPart1(gamma, epsilon, values);
	ProcessPart2(oxy, co2, values);
	
	std::cout << "Gamma: " << gamma << ", Epsilon: " << epsilon << ", solution: " << gamma * epsilon << '\n' <<
		"Oxygen: " << oxy << ", Carbon with two oxygens: " << co2 << ", solution: " << oxy * co2 << '\n';
}


std::vector<std::string> GetInputValues()
{
	std::ifstream input("input.txt", std::ios::in);
	
	std::vector<std::string> values = std::vector<std::string>();
	
	for(std::string line; std::getline(input, line);)
		values.push_back(line);
	
	return values;	
}


void ProcessPart1(unsigned int& gamma, unsigned int& epsilon, const std::vector<std::string>& values)
{
	unsigned int* counters = new unsigned int[values.at(0).size()];
	
	for(int i = 0; i < values.at(0).size(); i++)
		counters[i] = 0;
	
	for(std::string value : values)
		for(int i = 0; i < value.size(); i++)
			if (value[i] == '1')
				counters[i]++;
	
	for(int i = 0; i < values.at(0).size(); i++)
		if (counters[i] > (values.size() / 2))
			gamma += (1 << (values.at(0).size() - (i + 1)));
	
	epsilon = ~gamma;
	
	epsilon = epsilon & (UINT32_MAX >> (sizeof(unsigned int) * 8 - values.at(0).size()));
	
	delete[] counters;
}

void ProcessPart2(unsigned int& oxy, unsigned int& co2, const std::vector<std::string>& values)
{
	std::vector<std::string> 
		oxyFirst = values, 
		oxyLast = std::vector<std::string>(), 
		co2First = values, 
		co2Last = std::vector<std::string>();
	
	unsigned char major = 0, minor = 0;
	
	for(int l = 0; l< values.at(0).size(); l++)
	{
		if (oxyFirst.size() > 1)
		{
			int counter = 0;
			for(int o = 0; o < oxyFirst.size(); o++)
				if (oxyFirst.at(o).at(l) == '1')
					counter++;
			
			if (counter * 2 > oxyFirst.size()||counter * 2 == oxyFirst.size())
				major = '1';
			else 
				major = '0';
			
			for(int o = 0; o < oxyFirst.size(); o++)
				if (oxyFirst.at(o).at(l) == major)
					oxyLast.push_back(oxyFirst.at(o));
			
			oxyFirst = oxyLast;
			oxyLast.clear();
		}
		
		if (co2First.size() > 1)
		{
			int counter = 0;
			for(int c = 0; c < co2First.size(); c++)
				if (co2First.at(c).at(l) == '1')
					counter++;
		
			if (counter * 2 > co2First.size() || counter * 2 == co2First.size())
				major = '0';
			else 
				major = '1';
			
			for(int c = 0; c < co2First.size(); c++)
				if (co2First.at(c).at(l) == major)
					co2Last.push_back(co2First.at(c));
						
			co2First = co2Last;
			co2Last.clear();
		}
	}
	
	std::cout << oxyFirst.at(0) << " . " << co2First.at(0) << '\n';
	
	for(int l = 0; l < values.at(0).size(); l++)
	{
		if(oxyFirst.at(0).at(l) == '1')
			oxy += ( 1 << (values.at(0).size() - (l + 1)));
		
		if(co2First.at(0).at(l) == '1')
			co2 += ( 1 << (values.at(0).size() - (l + 1)));
	}
	
}





