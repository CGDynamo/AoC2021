#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

//( ) 40,  41
//[ ] 91,  93
//< > 60,  62
//{ } 123, 125

std::vector<std::string> GetDataChunks(const char* filename);
void FixChunkData(std::vector<std::string>& chunks);

int main ()
{
	std::vector<std::string> chunks = GetDataChunks("input.txt");
	FixChunkData(chunks);
}

std::vector<std::string> GetDataChunks(const char* filename)
{
	std::ifstream file(filename, std::ios::in);
	std::vector<std::string> chunks = std::vector<std::string>();
	for(std::string line; std::getline(file, line);)
		chunks.push_back(line);
	return chunks;
}

int GetValue(const char& c)
{
	switch(c)
	{
		case ')':
			return 3;
		case ']':
			return 57;
		case '}':
			return 1197;
		case '>':
			return 25137;
		default:
			return 0;
	}
}
int GetValueWhyDoesThisNeedToBeDifferent(const char& c)
{
	switch(c)
	{
		case ')':
			return 1;
		case ']':
			return 2;
		case '}':
			return 3;
		case '>':
			return 4;
		default:
			return 0;
	}
}

void FixChunkData(std::vector<std::string>& chunks)
{
	std::vector<std::pair<char,int>> oopsers = std::vector<std::pair<char,int>>();
	std::vector<std::vector<char>> whoopsers = std::vector<std::vector<char>>(); 

	for(int s = 0; s < chunks.size(); s++)
	{
		std::vector<char> commandStack = std::vector<char> ();
		bool badline = false;

		for(int c = 0; c < chunks.at(s).size(); c++)
		{
			char command = chunks.at(s).at(c);
			if(command == '(' || command == '[' || command == '{' || command ==  '<')
				commandStack.push_back(command);

			char comm = (commandStack.size() < 1)? ' ' : commandStack.at(commandStack.size()-1);
			
			if ( command == ')' )
			{
				if(comm != '(')
				{
					badline = true;
					oopsers.push_back(std::make_pair(')', s));
					chunks[s][c] = command + 2;
				}
				commandStack.pop_back();
			}
			
			if ( command == ']')
			{
				if(comm != '[')
				{
					badline = true;
					oopsers.push_back(std::make_pair(']', s));
					chunks[s][c] = ((command == '(')? ')' : command + 2);
				}
				commandStack.pop_back();
			}
			
			if (command == '}')
			{
				if(comm != '{')
				{
					badline = true;
					oopsers.push_back(std::make_pair('}', s));
					chunks[s][c] = ((command == '(')? ')' : command + 2);
				}
				commandStack.pop_back();
			}
			
			if (command == '>')
			{
				if(comm != '<' )
				{
					badline = true;
					oopsers.push_back(std::make_pair('>', s));
					chunks[s][c] = ((command == '(')? ')' : command + 2);
				}
				commandStack.pop_back();
			}
		}
		
		if (!badline)
		{
			std::vector<char> completioner = std::vector<char>();
			for(char command : commandStack)
				completioner.push_back((command == '(')? ')' : command + 2);
			std::reverse(completioner.begin(), completioner.end());
			whoopsers.push_back(completioner);
		}
	}
	
	long long 
		track = -1,
		sum = 0,
		whsum = 0;
	for(std::pair<char,int> pair : oopsers)
	{
		if (pair.second > track)
		{
			sum += GetValue(pair.first);
			track = pair.second;
		}		
	}
	std::cout << "Part 1 sum: " << sum << '\n';

	std::vector<long long> totals = std::vector<long long>();

	for(std::vector<char> whoops : whoopsers)
	{
		sum = 0;
		for(char c : whoops)
		{
			std::cout << c;
			sum = (sum * 5) + GetValueWhyDoesThisNeedToBeDifferent(c);
		}
		std::cout << '\n' << sum << '\n';
		totals.push_back(sum);
	}
	std::cout << '\n';
	std::sort(totals.begin(), totals.end());

	for(long long total : totals)
		std::cout << total << '\n';

	std::cout << "Part 2 sum: " << totals.at(totals.size()/2) << '\n';


}
