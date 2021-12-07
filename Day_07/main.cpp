#include <iostream>
#include <vector>

std::vector<int> GetPositions();
void GetEffeciency(const std::vector<int>& positions);

int main()
{
	std::vector<int> positions = GetPositions();
	return GetEffeciency(positions);
}

std::vector<int> GetPositions()
{
	FILE* file;
	errno_t err = fopen_s(&file, "input.txt", "rb");
	
	std::vector<int> positions = std::vector<int>();
	
	int c = 0, i = 0;
	
	while((c = getc(file)) != EOF)
		if(c > 47 && c < 58 )
			i = i * 10 + (c - 48);
		else
		{
			positions.push_back(i);
			i = 0;
		}
	positions.push_back(i);
		
	fclose(file);
	return positions;
}

int CalcFuelPlusDelta(const std::vector<int>& positions, const int& target)
{
	int sum = 0;
	for	(int i : positions)
		sum += abs(target - i);
	return sum;
}
int CalcFuelArithmaDelta(const std::vector<int>& positions, const int& target)
{
	int sum = 0;
	for	(int i : positions)
	{
		int dist = abs(target - i),
			humm = dist * ((dist + 1) / 2.0f);
		sum += humm;
	}
	return sum;
}

void GetEffeciency(const std::vector<int>& positions)
{	
	int min = INT_MAX,
		max = 0,
		avg = 0;
	
	for(int i : positions)
	{
		min = (i < min)? i : min;
		max = (i > max)? i : max;
	}
	
	int arit = INT_MAX, plus = INT_MAX, total1, total2;
	for (int i = min; i <= max; i++ )
	{
		int delta = CalcFuelPlusDelta(positions, i);
		int gamma = CalcFuelArithmaDelta(positions, i);
		if (delta < plus)
		{
			plus = delta;
			total1 = i; 
		}
		if (gamma < arit)
		{
			arit = gamma;
			total2 = i; 
		}
	}
	std::cout << "\nPart 1: " << plus << " fuel at " << total1 << " days\n";
	std::cout << "\nPart 2: " << arit << " fuel at " << total2 << " days\n";
}

