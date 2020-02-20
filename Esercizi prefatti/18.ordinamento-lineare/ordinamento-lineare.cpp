#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

pair<int*,int> countingSort(int *A, int n)
{
	int min=A[0];
	int max=A[0];
	for(int i=0;i<n;i++)
	{
		if(A[i]<min) min=A[i];
		if(A[i]>max) max=A[i];
	}
	int range=max-min+1;
	int *C = new int[range];
	for(int i=0;i<range;i++) C[i]=0;
	for(int i=0;i<n;i++) C[A[i]-min]++;
	for(int i=1;i<range;i++) C[i]+=C[i-1];
	int *B = new int[n];
	for(int i=n-1;i>=0;i--)
	{
		B[C[A[i]-min]-1]=A[i];
		C[A[i]-min]--;
	}
	for(int i=0;i<n;i++)
		A[i]=B[i];
	delete []B;
	return make_pair(C,range);
}

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	double* A;
	int* B;
	while(getline(input,line))
	{
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while(getline(substring,token,' '))
		{
			tokens.push_back(token);
		}
		char type = tokens[0].at(0);
		int n = stoi(tokens[1]);
		A = new double[n];
		for(int i=0;i<n;i++)
		{
			string value = tokens[i+2];
			double d = (type=='c') ?  (value[0]) : stod(value);
			A[i] = d;
		}
		B = new int[n];
		for(int i=0;i<n;i++)
		{
			if(type=='d')
				B[i]=(int)(A[i]*10);
			else
				B[i]=A[i];
		}
		int* C=countingSort(B,n).first;
		int k=countingSort(B,n).second;
		for(int i=0;i<k;i++)
			output << C[i] << " ";
		for(int i=0;i<n;i++)
		{
			if(type=='c')
				output << (char)B[i] << " ";
			else if(type=='d')
				output << ((double)B[i])/10 << " ";
			else
				output << B[i] << " ";
		}
		output << endl;
		
		delete[] A;
		delete[] B;
	}
	input.close();
	output.close();
	return 1;
}
