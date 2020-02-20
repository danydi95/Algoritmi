#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

pair<int*,int> countingSort(pair<int,int> *A, int n)
{
	int min=A[0].first;
	int max=A[0].first;
	for(int i=0;i<n;i++)
	{
		if(A[i].first<min) min=A[i].first;
		if(A[i].first>max) max=A[i].first;
	}
	int range=max-min+1;
	int *C = new int[range];
	for(int i=0;i<range;i++) C[i]=0;
	for(int i=0;i<n;i++) C[A[i].first-min]++;
	for(int i=1;i<range;i++) C[i]+=C[i-1];
	pair<int,int> *B = new pair<int,int>[n];
	for(int i=n-1;i>=0;i--)
	{
		B[C[A[i].first-min]-1]=A[i];
		C[A[i].first-min]--;
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
	pair<double,double> *A;
	pair<int,int>* B;
	while(getline(input,line))
	{
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while(getline(substring,token,' '))
			tokens.push_back(token);
		int n = stoi(tokens[0]);
		A = new pair<double,double>[n];
		for(int i=0,j=0;i<2*n,j<n;i++)
		{
			string value = tokens[i+1];
			if(value.at(0)=='(')
			{
				string s1 = value.erase(0,1);
				double d1 = stod(s1);
				A[j].first = d1;
				//cout << "Inserisco " << A[j].first << " in " << j << endl;
				j++;
			}
		}
		for(int i=0,j=0;i<2*n,j<n;i++)
		{
			string value = tokens[i+1];
			if(value.at(0)!='(')
			{
				string s2 = value.erase(value.length()-1,value.length());
				double d2 = stod(s2);
				A[j].second = d2;
				//cout << "Inserisco " << A[j].second << " in " << j << endl;
				j++;
			}
		}
		B = new pair<int,int>[n];
		for(int i=0;i<n;i++)
		{
			B[i].first = (int)((A[i].first)*10);
			B[i].second = (int)((A[i].second)*10);
			//cout << B[i].first << "," << B[i].second << " ";
		}
		int* C=countingSort(B,n).first;
		int k=countingSort(B,n).second;
		for(int i=0;i<k;i++)
			output << C[i] << " ";
		for(int i=0;i<n;i++)
			output << "(" << (double)B[i].first/10 << " " << (double)B[i].second/10 << ") ";
		output << endl;
		
		delete[] A;
		delete[] B;
	}
	input.close();
	output.close();
	return 1;
}
