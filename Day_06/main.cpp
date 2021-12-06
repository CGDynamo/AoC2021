#include <iostream>
#include <vector>


std::vector<char> GetFishies();
unsigned long long BreedFishies(const int& days, const std::vector<char>& fishies);

int main()
{	
	std::vector<char> fishies = GetFishies();
	
	std::cout << "After 256 days: "<<  BreedFishies( 256, fishies) <<" fishies remain.\n";
	return 0;
}

std::vector<char> GetFishies()
{
	FILE* file;
	errno_t err = fopen_s(&file, "input.txt", "rb");
	std::vector<char> fishies = std::vector<char>();

	do fishies.push_back(getc(file) - 48);
	while (getc(file) != EOF);
	
	fclose(file);
	return fishies;
}

unsigned long long BreedFishies(const int& days, const std::vector<char>& fishies)
{
	std::vector<int> newFishies = std::vector<int>();
	unsigned long long sum = fishies.size();
	
	for(char fish : fishies)
		for	(int remaining = days - fish; remaining > 0; remaining -= 7)
			newFishies.push_back(remaining - 9);
	
	
	while (newFishies.size() > 0)
	{
		sum++;
		int fish = newFishies.at(newFishies.size()-1);
		newFishies.pop_back();
		for	(int remaining = fish; remaining > 0; remaining -= 7)
			newFishies.push_back(remaining - 9);
		if (sum % 1000000 == 0 && fish < 0)
			std::cout << "At " << sum << ", quant: " <<newFishies.size() << '\n';
	}
	return sum;
}
