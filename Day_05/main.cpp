#include <iostream>
#include <vector> 
#include <fstream>
#include <string>


struct Point2
{
	int x,y;
	Point2(int _x, int _y): x(_x), y(_y) { }
};

std::vector<std::pair<Point2, Point2>> ParseInputs(int& mapWidth, int& mapHeight);
void FillMap(const std::vector<std::pair<Point2, Point2>>& inputs, int* map, const int& mapWidth, const int& mapHeight, const bool& part2);
int CountCollisions(const int* map, const int& mapWidth, const int& mapHeight);

int main()
{
	int mapWidth = 0, mapHeight = 0;
	std::vector<std::pair<Point2, Point2>> inputs = ParseInputs(mapWidth, mapHeight);
	
	int* map = new int[mapWidth * mapHeight];
	int* map2 = new int[mapWidth * mapHeight];
	for(int i = 0; i < mapWidth * mapHeight; i++)
		map[i] = map2[i]= 0;
	
	FillMap(inputs, map, mapWidth, mapHeight, false);
	FillMap(inputs, map2, mapWidth, mapHeight, true);
	
	std::cout << "Part 1: " << CountCollisions(map, mapWidth, mapHeight)  << "\nPart 2: " << CountCollisions(map2, mapWidth, mapHeight) << '\n';
	
	return 0;
}


std::vector<std::pair<Point2, Point2>> ParseInputs(int& mapWidth, int& mapHeight)
{
	std::vector<std::pair<Point2, Point2>> inputs;
	std::ifstream file("input.txt", std::ios::in);
	
	for(std::string line; std::getline(file, line);)
	{
		Point2 start = {0,0}, end = {0,0};
		
		std::string manual = "";
		char entry = 0;
		for(char c : line)
		{
			if (c > 47 && c < 58) //ascii table cheating
				manual.push_back(c);
			else if (manual.size() > 0)
			{
				int indpart = std::stoi(manual);
				switch(entry)
				{
					case 0:
						start.x = indpart;
						if (indpart > mapWidth)
							mapWidth = indpart + 1;
						break;
					case 1:
						start.y = indpart;
						if (indpart > mapHeight)
							mapHeight = indpart + 1;
						break;
					case 2:
						end.x = indpart;
						if (indpart > mapWidth)
							mapWidth = indpart + 1;
						break;
				}
				entry++;
				manual.clear();
			}
			
		}

		end.y = std::stoi(manual);
		if (end.y > mapHeight)
			mapHeight = end.y+ 1;
		
		inputs.push_back(std::make_pair(start, end));
	}
	
	return inputs;
}


void FillMap(const std::vector<std::pair<Point2, Point2>>& inputs, int* map, const int& mapWidth, const int& mapHeight, const bool& part2)
{
	for(std::pair<Point2, Point2> pair : inputs)
		if (pair.first.x == pair.second.x)
		{			
			Point2 ySpan = (pair.first.y < pair.second.y) ? 
				Point2( pair.first.y, pair.second.y ) : Point2( pair.second.y, pair.first.y );
			for(int y = ySpan.x; y <= ySpan.y; y++)
				map[pair.first.x + y * mapWidth] += 1;
		}
		else if (pair.first.y == pair.second.y)
		{
			Point2 xSpan = (pair.first.x < pair.second.x) ? 
				Point2( pair.first.x, pair.second.x ) : Point2( pair.second.x, pair.first.x);
			for(int x = xSpan.x; x <= xSpan.y; x++)
				map[x + pair.first.y * mapWidth] += 1;
		}
		else if (abs(pair.first.x - pair.second.x) == abs(pair.first.y - pair.second.y) && part2)
		{
			std::cout << "(" << pair.first.x << ", " << pair.first.y << ") - (" << pair.second.x << ", " << pair.second.y << ")" << abs(pair.first.x - pair.second.x) << " | " << abs(pair.first.y - pair.second.y) << '\n';
			int signX = (pair.first.x - pair.second.x < 0)? 1 : -1,
				signY = (pair.first.y - pair.second.y < 0)? 1 : -1;
				
			for(int i = 0; i <= abs(pair.first.x - pair.second.x); i++)
				map[pair.first.x + i * signX + (pair.first.y + i * signY) * mapWidth] += 1;
			
		} 
}



int CountCollisions(const int* map, const int& mapWidth, const int& mapHeight)
{
	int counter = 0;
	
	for(int y = 0; y < mapHeight; y++)
		for(int x = 0; x < mapWidth; x++)
			if(map[x + y * mapWidth] > 1)
				counter++;
			
	return counter;	
}