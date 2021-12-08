#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

// 0 : 6 (a,b,c,e,f,g)
// 1 : 2 (c,f)
// 2 : 5 (a,c,d,e,f)
// 3 : 5 (a,c,d,f,g)
// 4 : 4 (b,c,d,f)
// 5 : 5 (a,b,d,f,g)
// 6 : 6 (a,b,d,e,f,g)
// 7 : 3 (a,c,f)
// 8 : 7 (a,b,c,d,e,f,g)
// 9 : 6 (a,b,c,d,f,g)

void ParseInputs(const char* filename, std::vector<std::vector<std::string>>& inputs, std::vector<std::vector<std::string>>& outputs);

void DeriveDemDigits(int& sum, std::vector<std::string>& iput, std::vector<std::string>& oput);

int main()
{
	std::vector<std::vector<std::string>>
		inputs = std::vector<std::vector<std::string>>(),
		outputs = std::vector<std::vector<std::string>>();
	
	ParseInputs("input.txt", inputs, outputs);
	int total = 0;
	for(int s = 0; s < inputs.size(); s++)
		DeriveDemDigits(total, inputs[s], outputs[s]);
	std::cout << total << '\n';
}

void ParseInputs(const char* filename, std::vector<std::vector<std::string>>& inputs, std::vector<std::vector<std::string>>& outputs)
{
	std::ifstream file(filename, std::ios::in);
	std::string tempString;
	
	for(std::string line; std::getline(file, line);)
	{
		std::vector<std::string> 
			parts = std::vector<std::string>(),
			baseIn = std::vector<std::string>(),
			baseOut = std::vector<std::string>();
		std::stringstream stream(line);
		
		while(getline(stream, tempString, '|'))
			parts.push_back(tempString);
		
		stream = std::stringstream(parts.at(0));
		while(getline(stream, tempString, ' '))
			if (tempString.size() > 0)
			{
				std::sort(tempString.begin(), tempString.end());
				baseIn.push_back(tempString);
			}
			
		inputs.push_back(baseIn);
		
		stream = std::stringstream(parts.at(1));
		while(getline(stream, tempString, ' '))
			if (tempString.size() > 0)
			{
				std::sort(tempString.begin(), tempString.end());
				baseOut.push_back(tempString);
			}
			
		outputs.push_back(baseOut);
	}
	
}


void DeriveDemDigits(int& sum, std::vector<std::string>& iput, std::vector<std::string>& oput)
{
	std::vector<int> 
		ins = std::vector<int>(iput.size()), 
		outs = std::vector<int>(oput.size());
	
	for(int i = 0; i < ins.size(); i++)
		ins[i] = -1;
	for(int i = 0; i < outs.size(); i++)
		outs[i] = -1;
	
	unsigned char segment[10] = {0,0,0,0,0,0,0,0,0,0};
	
	//find 1,7,4,and eight
	for(int i = 0; i < iput.size(); i++)
		switch(iput[i].size())
		{
			case 2: //1
				ins[i] = 1; 
				segment[1] = 0;
				for(char c : iput[i])
					segment[1] += 1 << (c - 97);
				break;
			case 3: //7
				ins[i] = 7;
				segment[7] = 0;
				for(char c : iput[i])
					segment[7] += 1 << (c - 97);
				break;
			case 4: //4
				ins[i] = 4;
				segment[4] = 0;
				for(char c : iput[i])
					segment[4] += 1 << (c - 97);
				break;
			case 7: //8
				ins[i] = 8;
				segment[8] = 0;
				for(char c : iput[i])
					segment[8] += 1 << (c - 97);
				break;
		}
		
		for(int i = 0; i < oput.size(); i++)
		switch(oput[i].size())
		{
			case 2: //1
				outs[i] = 1; 
				segment[1] = 0;
				for(char c : oput[i])
					segment[1] += 1 << (c - 97);
				break;
			case 3: //7
				outs[i] = 7;
				segment[7] = 0;
				for(char c : oput[i])
					segment[7] += 1 << (c - 97);
				break;
			case 4: //4
				outs[i] = 4;
				segment[4] = 0;
				for(char c : oput[i])
					segment[4] += 1 << (c - 97);
				break;
			case 7: //8
				outs[i] = 8;
				segment[8] = 0;
				for(char c : oput[i])
					segment[8] += 1 << (c - 97);
				break;
		}
		
		
	for(int i = 0; i < iput.size(); i++)		
		if (ins[i] == -1)
		{
			unsigned char possible = 0;
			for(char c : iput[i])
				possible += 1 << (c - 97);
			
			if (iput[i].size() == 6 && (possible & segment[1]) == segment[1] && (possible & segment[4]) == segment[4] && (possible & segment[7]) == segment[7])
				segment[ins[i] = 9] = possible;
			else if(iput[i].size() == 5&& (possible & segment[1]) == segment[1] && (possible & segment[7]) == segment[7])
				segment[ins[i] = 3] = possible;
			else if(iput[i].size() == 6 && (possible & segment[1]) == segment[1] && (possible & segment[7]) == segment[7])
				segment[ins[i] = 0] = possible;
					
		}
	for(int i = 0; i < oput.size(); i++)		
		if (outs[i] == -1)
		{
			unsigned char possible = 0;
			for(char c : oput[i])
				possible += 1 << (c - 97);
			
			if (oput[i].size() == 6 && (possible & segment[1]) == segment[1] && (possible & segment[4]) == segment[4] && (possible & segment[7]) == segment[7])
				segment[outs[i] = 9] = possible;
			else if(oput[i].size() == 5 && (possible & segment[1]) == segment[1] && (possible & segment[7]) == segment[7])
				segment[outs[i] = 3] = possible;
			else if(oput[i].size() == 6 && (possible & segment[1]) == segment[1] && (possible & segment[7]) == segment[7])
				segment[outs[i] = 0] = possible;					
		}
		
	for(int i = 0; i < iput.size(); i++)		
		if (ins[i] == -1)
		{
			unsigned char possible = 0;
			for(char c : iput[i])
				possible += 1 << (c - 97);
			
			if (iput[i].size() == 5 && (possible & (segment[1] ^ segment[4])) == (segment[1] ^ segment[4]))
				segment[ins[i] = 5] = possible;	
			else if (iput[i].size() == 5 && (possible & (segment[8] ^ segment[9])) == (segment[8] ^ segment[9]))
				segment[ins[i] = 2] = possible;	
			else if (iput[i].size() == 6)
				segment[ins[i] = 6] = possible;				
		}		
		
	for(int i = 0; i < oput.size(); i++)		
		if (outs[i] == -1)
		{
			unsigned char possible = 0;
			for(char c : oput[i])
				possible += 1 << (c - 97);
			
			if (oput[i].size() == 5 && (possible & (segment[1] ^ segment[4])) == (segment[1] ^ segment[4]))
				segment[outs[i] = 5] = possible;	
			else if (oput[i].size() == 5 && (possible & (segment[8] ^ segment[9])) == (segment[8] ^ segment[9]))
				segment[outs[i] = 2] = possible;	
			else if (oput[i].size() == 6)
				segment[outs[i] = 6] = possible;					
		}		
			
		
	for(int i : ins)
		std::cout << ((i < 0)? (char)'*' : (char)(i+48));
	std::cout << " | ";
	for(int i : outs)
		std::cout << ((i < 0)? (char)'*' : (char)(i+48));
	std::cout << '\n';
	
	int boggle = 0;
	for(int i = 0; i < outs.size(); i++)
		boggle = boggle*10 + outs[i];
	sum += boggle;
return;	
	
}