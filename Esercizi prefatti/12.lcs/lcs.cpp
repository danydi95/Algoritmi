#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int max(int i,int j)
{
	if(i>j) return i;
	else return j;
}

int computeLCS(char* string1, char* string2, int n,int m)
{
	vector<vector<int>> lookUp = vector<vector<int>>(n+1, vector<int>(m+1,0));
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j <= m; j++) 
		{
			if (string1[i - 1] == string2[j - 1])
				lookUp[i][j] = lookUp[i - 1][j - 1] + 1;
			else
				lookUp[i][j] = max(lookUp[i - 1][j], lookUp[i][j - 1]);
		}
	}	
	return lookUp[n][m];
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
		char* x = new char[n];
		char* y = new char[m];
		for(int i=0;i<n;i++)
			x[i]=tokens[2].at(i);
		for(int i=0;i<m;i++)
			y[i]=tokens[3].at(i);
		output << computeLCS(x,y,n,m) << endl;
		
		delete[] x;
		delete[] y;
	}
	input.close();;
	output.close();
	return 1;
}
