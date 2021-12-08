#include <stdio.h>
#include <chrono>

const char Data[] = {1, 1, 1, 1, 1, 1, 1, 4, 1, 2, 1, 1, 4, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 3, 1, 1, 2, 1, 2, 1, 3, 3, 4, 1, 4, 1, 1, 3, 1, 1, 5, 1, 1, 1, 1, 4, 1, 1, 5, 1, 1, 1, 4, 1, 5, 1, 1, 1, 3, 1, 1, 5, 3, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 2, 4, 1, 1, 1, 1, 4, 1, 2, 2, 1, 1, 1, 3, 1, 2, 5, 1, 4, 1, 1, 1, 3, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 5, 1, 1, 1, 4, 1, 1, 5, 1, 1, 5, 3, 3, 5, 3, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 5, 3, 1, 2, 1, 1, 1, 4, 1, 3, 1, 5, 1, 1, 2, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 4, 3, 2, 1, 2, 4, 1, 3, 1, 5, 1, 2, 1, 4, 1, 1, 1, 1, 1, 3, 1, 4, 1, 1, 1, 1, 3, 1, 3, 3, 1, 4, 3, 4, 1, 1, 1, 1, 5, 1, 3, 3, 2, 5, 3, 1, 1, 3, 1, 3, 1, 1, 1, 1, 4, 1, 1, 1, 1, 3, 1, 5, 1, 1, 1, 4, 4, 1, 1, 5, 5, 2, 4, 5, 1, 1, 1, 1, 5, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1};
//const char Data[] = {3, 4, 3, 1, 2};
unsigned long long BreedingDays[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned int Today = 0;

int main(int argc, char *argv[])
{    
	//get start time for operation(s)
	auto startOp = std::chrono::high_resolution_clock::now();

    int iterator = 0, dayCount = 0;
    char c;
    if (argc < 2)
        return -1;
    while ((c = argv[1][iterator++]) != '\0')
        dayCount = dayCount * 10 + (c - 48);

    int day = 0;

    for (int i = 0; i < sizeof(Data); i++)
        BreedingDays[(Data[i])] += 1;

    unsigned long long temp;
    while (day <= dayCount)
    {
        temp = BreedingDays[(day + 6) % 7];
        BreedingDays[(day + 6) % 7] += BreedingDays[7];
        BreedingDays[7] = BreedingDays[8];
        BreedingDays[8] = temp;
        day++;
    }

    unsigned long long total = 0;
    for (size_t i = 0; i < 9; i++)
    {
        total += BreedingDays[i];
    }
    
	//get end of operation time and get the difference
	auto stopOp = std::chrono::high_resolution_clock::now();
	unsigned long long elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(stopOp - startOp).count();
    
    printf("After %d days, fishcount %llu, after elapsed %llu\n", day-1, total, elapsed);

    return 0;
}