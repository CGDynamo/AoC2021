#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>

struct Card
{
	char points[5][5];
	bool marked[5][5];
};

std::vector<char> ParseCalls();
std::vector<Card> ParseCards();
Card FindFirstWinner(const std::vector<Card>& cards);
int CalculateScore(const Card& card, const char& call);


main()
{
	std::vector<char> calls = ParseCalls();
	std::vector<Card> cards = ParseCards();
		
	for(int c = 0; c < cards.size(); c++)
		std::cout << (int)cards.at(c).points[0][0] << " | "<< (int)cards.at(c).points[4][4] << '\n';
	
}


std::vector<char> ParseCalls()
{
	std::ifstream file("input.txt", std::ios::in);
	
	std::string callLine;
	std::getline(file, callLine);
	std::vector<char> calls = std::vector<char>();
	
	std::string call = "";
	
	for(char c : callLine)
	{
		if (c == ',')
		{
			calls.push_back(std::stoi(call));
			call.clear();
		}
		else
			call.push_back(c);
	}	
	calls.push_back(std::stoi(call));
	
	return calls;
}

std::vector<Card> ParseCards()
{
	std::vector<Card> cards = std::vector<Card>();
	
	std::ifstream file("input.txt", std::ios::in);
	
    int counter = -1;	
	Card card = Card();
	
	for(std::string line; std::getline(file, line);)
	{
		if (counter >= 0 && counter % 6 != 0)
		{
			int y = counter % 6;
			for(int x = 0; x < 5; x++)
			{
				std::string stringlette = line.substr(x*3,3);
				std::remove(stringlette.begin(), stringlette.end(), ' ');
				card.points[y - 1][x] = std::stoi(stringlette);
				card.marked[y - 1][x] = false;
			}
		}
		else if (counter > 0 && counter % 6 == 0)
		{
			cards.push_back(card);
		}
		counter ++;
	}
	return cards;
}

Card FindFirstWinner(const std::vector<Card>& cards)
{
	
	
	return Card();
}

int CalculateScore(const Card& card, const char& call)
{
	
	return 0;
}
