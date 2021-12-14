#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::pair<char,int>> OpenFile(int& width, const char* filename);
std::vector<std::pair<char,int>>FindLowpoints(const int& width, const std::vector<std::pair<char,int>>& values);
std::vector<std::vector<int>> FindBasins(const int& width, const std::vector<std::pair<char,int>>& values, const std::vector<std::pair<char,int>>& lowpoints);

int main()
{
	int width = 0;
	std::vector<std::pair<char,int>> values = OpenFile(width, "input.txt");
	std::vector<std::pair<char,int>> lowpoints = FindLowpoints(width, values);
		
	int totalPart1 = 0;
	for(std::pair<char, int> c : lowpoints)
		totalPart1 += c.first;
	
	std::cout << "\nPart1 :" << totalPart1 + lowpoints.size() << '\n';
	std::vector<std::vector<int>> basins = FindBasins(width, values, lowpoints);
	return 0;
}


std::vector<std::pair<char,int>> OpenFile(int& width, const char* filename)
{
	FILE* file;
	errno_t err = fopen_s(&file, filename, "rb");
	std::vector<std::pair<char,int>> values = std::vector<std::pair<char,int>>();
	
	char c;
	int counter = 0;
	while ((c = getc(file)) != EOF)
		if (c > 47 && c < 58)
		{
			values.push_back(std::make_pair(c-48, counter));
			counter++;
		}
		else if (width == 0)
			width = counter;
	
	fclose(file);
	return values;
}

std::vector<std::pair<char,int>>FindLowpoints(const int& width, const std::vector<std::pair<char,int>>& values)
{
	std::vector<std::pair<char,int>> lowpoints = std::vector<std::pair<char,int>>();
	int height = values.size()/width;
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			char 
				point = values[x + y * width].first,
				north = (y + 1 >= height)? 127 : values[x + (y + 1) * width].first, 
				south = (y - 1 < 0)? 127 : values[x + (y - 1) * width].first, 
				east = (x + 1 >= width)? 127 : values[x + 1 + y * width].first, 
				west = (x - 1 < 0)? 127 : values[x - 1 + y * width].first; 
				
			if ( point < north && point < south && point < east && point < west )
				lowpoints.push_back(std::make_pair(point, x + y * width));
		}
		
	return lowpoints;
}

void GetNeighbors(int* grid, const int& iteration, const int& index, const int& width, const std::vector<std::pair<char,int>>& values)
{
	std::vector<int> neighbors = std::vector<int>();
	
	int x = index % width,
		y = index / width,
		height = values.size() / width;
	
	if(x - 1 >= 0 && grid[index - 1] == 0 && values[index - 1].first != 9)
	{
		grid[index - 1] = iteration;
		neighbors.push_back(index - 1);
	}
	
	if(x + 1 < width && grid[index + 1] == 0 && values[index + 1].first != 9)
	{
		grid[index + 1] = iteration;
		neighbors.push_back(index + 1);
	}
	
	if(y - 1 >= 0 && grid[index - width] == 0 && values[index - width].first != 9)
	{
		grid[index - width] = iteration;
		neighbors.push_back(index - width);
	}
	
	if(y + 1 < height && grid[index + width] == 0 && values[index + width].first != 9)
	{
		grid[index + width] = iteration;
		neighbors.push_back(index + width);
	}	
	for(int i : neighbors)
		GetNeighbors(grid, iteration, i, width, values);
			
}

std::vector<std::vector<int>> FindBasins(const int& width, const std::vector<std::pair<char,int>>& values, const std::vector<std::pair<char,int>>& lowpoints)
{
	int* grid = new int[values.size()];
	for(int i = 0; i < values.size(); i ++)
		grid[i] = 0;
	
	std::vector<std::vector<int>> basins = std::vector<std::vector<int>>();

	for(int lowpair = 0; lowpair < lowpoints.size(); lowpair++)
	{		
		int index = lowpoints[lowpair].second;
		
		if (grid[index] == 0)
		{
			std::vector<int> basin = std::vector<int>();
			
			GetNeighbors(grid, lowpair + 1, index, width, values);
			
			int total = 0;
			for(int i = 0; i < values.size(); i ++)
				if (grid [i] == lowpair+1)
					basin.push_back(values[i].first);
				
			basins.push_back(basin);
			
		}		
	}
	
		
	int	height = values.size() / width;
	FILE* file;
	errno_t err = fopen_s(&file,"output.txt","wb");
	for(int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			putc(91, file);
			putc(((grid[x+y*width] == 0) ? ' ' : (char)((grid[x+y*width] % 26) + 97)), file);
			putc(93, file);
		}
		putc(13,file);
		putc(10,file);		
	}
	fclose(file);
		
	
	std::vector<int> lazy = std::vector<int>();
	for (std::vector<int> basin : basins)
	{
		std::cout << basin.size() << ", ";
		lazy.push_back(basin.size());
	}
	
	std::sort(lazy.begin(), lazy.end());
	std::reverse(lazy.begin(), lazy.end());
	
	std::cout << "\nPart2 :" << '[' << lazy[0] << "] [" << lazy[1] << "] [" << lazy[2] << "] " << lazy[0] * lazy[1] * lazy[2] << '\n';
	
	return basins;
}