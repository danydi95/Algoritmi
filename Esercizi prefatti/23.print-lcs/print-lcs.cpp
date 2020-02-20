#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int max(int a,int b)
{
	if(a>b) return a;
	else return b;
}

int computeLCS(string& string1, string& string2, string& lcs)
{
	int n = string1.length();
	int m = string2.length();
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
	lcs.resize(lookUp[n][m]);	
	int i = n, j = m;
	while (i > 0 && j > 0)
	{
		if (string1[i - 1] == string2[j - 1])
		{
			lcs[lookUp[i][j] - 1] = string1[i - 1];
			i--;
			j--;			
		}
		else if (lookUp[i - 1][j] > lookUp[i][j - 1])
			i--;
		else
			j--;
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
		string x="";
		string y="";
		string lcs="";
		for(int i=0;i<n;i++)
			x+=tokens[2].at(i);
		for(int i=0;i<m;i++)
			y+=tokens[3].at(i);
		computeLCS(x,y,lcs);
		output << lcs << endl;
	}
	input.close();;
	output.close();
	return 1;
}
