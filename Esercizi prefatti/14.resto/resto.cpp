#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#define min(A,B) A<B ? A : B

using namespace std;

int minCoins(int coins[], int m, int V) 
{ 
    int table[V+1]; 
    table[0] = 0; 
    for (int i=1; i<=V; i++) 
        table[i] = INT_MAX; 
    for (int i=1; i<=V; i++) 
    {  
        for (int j=0; j<m; j++) 
          if (coins[j] <= i) 
          { 
              int sub_res = table[i-coins[j]]; 
              if (sub_res != INT_MAX && sub_res + 1 < table[i]) 
                  table[i] = sub_res + 1; 
          } 
    } 
    return table[V]; 
} 

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	while(getline(input,line))
	{
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while(getline(substring,token,' '))
		{
			tokens.push_back(token);
		}
		int resto=stoi(tokens[0]);
		int ntagli=stoi(tokens[1]);
		int* tagli = new int[ntagli];
		for(int i=0;i<ntagli;i++)
			tagli[i]=stoi(tokens[i+2]);
		output << minCoins(tagli,ntagli,resto) << endl;		
	}
	input.close();
	output.close();
	return 1;
}
