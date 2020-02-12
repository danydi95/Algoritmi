#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#define min(A,B) A<B ? A : B
#define CANC 1
#define INS 1
#define REP 1
#define COPY 0

using namespace std;

int computeEditDistance(string& x, string& y, vector<vector<int>>& lookUp)
{
	int edge_number = x.length();
	int node_number = y.length();
	lookUp = vector<vector<int>>(edge_number + 1, vector<int>(node_number + 1, 0));
	for (int i = 1; i <= edge_number; i++)
		lookUp[i][0] = lookUp[i - 1][0] + CANC;
	for (int j = 1; j <= node_number; j++)
		lookUp[0][j] = lookUp[0][j - 1] + INS;
	for (int i = 1; i <= edge_number; i++)
		for (int j = 1; j <= node_number; j++)
		{
			if (x[i - 1] == y[j - 1])
				lookUp[i][j] = lookUp[i - 1][j - 1] + COPY;
			else
			{
				int tmp = min(lookUp[i - 1][j] + CANC, lookUp[i][j - 1] + INS);
				lookUp[i][j] = min(tmp, lookUp[i - 1][j - 1] + REP);    
			}
		}
	return lookUp[edge_number][node_number];
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
		double** A;
		while(getline(substring,token,' '))
		{
			tokens.push_back(token);
		}
		int n=stoi(tokens[0]);
		int m=stoi(tokens[1]);
		string s1=tokens[2];
		string s2=tokens[3];
		vector<vector<int>> z;
		output << computeEditDistance(s1,s2,z) << endl;
		
	}
	input.close();;
	output.close();
	return 1;
}
