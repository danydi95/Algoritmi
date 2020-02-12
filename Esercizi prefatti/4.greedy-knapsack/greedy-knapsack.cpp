#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int extractMax(int *A,int n)
{
	int max=0;
	for(int i=0;i<n;i++)
	{
		if(A[i]>max) max=A[i];
	}
	for(int i=0;i<n;i++)
	{
		if(A[i]==max)
		{
			A[i]=-1;
			break;
		}
	}
	return max;
}

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	int* A;
	while(getline(input,line))
	{
		int operations=0;
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while(getline(substring,token,' '))
		{
			tokens.push_back(token);
		}
		operations=stoi(tokens[0]);
		int weight=stoi(tokens[1]);
		A = new int[operations];
		for(int i=0;i<operations;i++)
		{
			A[i]=(stoi(tokens[i+2]));
		}
		int total=0;
		for(int i=0;i<weight;i++)
		{
			int max=extractMax(A,operations);
			total+=max;
		}
		output << total << endl;
		delete[] A;
	}
	input.close();;
	output.close();
	return 1;
}
