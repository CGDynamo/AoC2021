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
std::vector<Card*> ParseCards();
Card* FindFirstWinner(const std::vector<char>& calls, std::vector<Card*> cards);
int CalculateScore(Card* card, const char& call);


main()
{
	std::vector<char> calls = ParseCalls();
	std::vector<Card*> cards = ParseCards();
		
	FindFirstWinner(calls, cards);
	
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

std::vector<Card*> ParseCards()
{
	std::vector<Card*> cards = std::vector<Card*>();
	
	std::ifstream file("input.txt", std::ios::in);
	
    int counter = -1;	
	Card* card = new Card();
	
	for(std::string line; std::getline(file, line);)
	{
		if (counter >= 0 && counter % 6 != 0)
		{
			int y = counter % 6;
			for(int x = 0; x < 5; x++)
			{
				std::string stringlette = line.substr(x*3,3);
				card->points[y - 1][x] = std::stoi(stringlette);
				card->marked[y - 1][x] = false;
			}
		}
		else if (counter > 0 && counter % 6 == 0)
		{
			cards.push_back(card);
			card = new Card();
		}
		counter ++;
	}
	cards.push_back(card);
	return cards;
}

bool Bingo(Card* card)
{
	bool rows[] = { true,true,true,true,true };
	bool cols[] = { true,true,true,true,true };
	
	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 5; x++)
			if (card->marked[y][x] == false)
			{
				rows[x] = false;
				cols[y] = false;
			}
			
	for(int i = 0; i < 5; i++)
		if (rows[i] == true || cols[i] == true)
			return true;
	
	return false;
}

Card* FindFirstWinner(const std::vector<char>& calls, std::vector<Card*> cards)
{
	int counter = cards.size();
	for(char call : calls)
		for(int c = 0; c < cards.size(); c++)
		{
			for(int y = 0; y < 5; y++)
				for(int x = 0; x < 5; x++)
					if(call == cards[c]->points[y][x])
						cards[c]->marked[y][x] = true;
			
			if(Bingo(cards[c]))
			{
				if (cards.size() == counter)
					std::cout << "part 1 BINGO! " << CalculateScore(cards[c], call) << '\n';
				if (cards.size() > 1)
				{
					cards.erase(cards.begin() + c);
					c--;
				}
				else
				{
					std::cout << "part 2 BINGO! " << CalculateScore(cards[c], call) << '\n';
					return cards[c];
				}
			}
		}
		
	std::cout << "winner not found!\n";
	return nullptr;
}

int CalculateScore(Card* card, const char& call)
{
	int score = 0;
	for(int y  = 0; y < 5; y++)
		for(int x  = 0; x < 5; x++)
			if (!card->marked[y][x])
				score += card->points[y][x];
	return score * call;
}
