#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void print(int* A,int* B,int k,int n,ofstream& output)
{
	for(int i=0;i<k;i++)
		output << A[i] << " ";
	for(int i=0;i<n;i++)
		output << B[i] << " ";
	output << endl;
}


void countingSort(int* A,int n,ofstream& output)
{
	int max=A[0];
	int min=A[0];
	for(int i=0;i<n;i++)
	{
		if(A[i]>max) max=A[i];
		if(A[i]<min) min=A[i];	
	}
	int range=max-min+1;
	int *C = new int[range];
	for(int i=0;i<range;i++) C[i]=0;
	for(int i=0;i<n;i++) C[A[i]-min]++;
	for(int i=1;i<range;i++) C[i]=C[i]+C[i-1];
	int *B = new int[n];
	for(int i=n-1;i>=0;i--)
	{
		B[C[A[i]-min]-1]=A[i];
		C[A[i]-min]--;
	}
	for(int i=0;i<n;i++)
		A[i]=B[i];
	print(C,A,range,n,output);
	delete[] C;
	delete[] B;
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
		A = new int[operations];
		for(int i=0;i<operations;i++)
			A[i]=stoi(tokens[i+1]);
	
		countingSort(A,operations,output);
		delete[] A;
	}
	input.close();;
	output.close();
	return 1;
}
