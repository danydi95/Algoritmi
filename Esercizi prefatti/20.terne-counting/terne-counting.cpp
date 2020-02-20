#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

pair<int*,int> countingSort(pair<int,pair<int,int>> *A, int n)
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
	pair<int,pair<int,int>> *B = new pair<int,pair<int,int>>[n];
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
	pair<double,pair<double,double>> *A;
	pair<int,pair<int,int>>* Z;
	double *B,*C,*D;
	while(getline(input,line))
	{
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while(getline(substring,token,' '))
			tokens.push_back(token);
		int n = stoi(tokens[0]);
		A = new pair<double,pair<double,double>>[n];
		B = new double[n];
		C = new double[n];
		D = new double[n];
		int j=0,z=0,o=0;
		for(int i=0;i<3*n,j<n,o<n,z<n;i++)
		{
			string value=tokens[i+1];
			if(value.at(0)=='(')
			{
				string s1=value.erase(0,1);
				double d1 = stod(s1);
				B[j]=d1;
				//cout << "Inserisco " << B[j] << " in " << j << endl;
				j++;
			}
			else
			{
				if(value.at(value.length()-1)==')')
				{
					string s2=value.erase(value.length()-1,value.length());
					double d2 = stod(s2);
					C[z]=d2;
					//cout << "Inserisco " << C[z] << " in " << z << endl;
					z++;
				}
				else
				{
					double d3 = stod(value);
					D[o]=d3;
					//cout << "Inserisco " << D[o] << " in " << o << endl;
					o++;
				}
			}
		}
		for(int i=0;i<n;i++)
		{
			pair<double,double> tmp = make_pair(D[i],C[i]);
			pair<double,pair<double,double>> x = make_pair(B[i],tmp);
			A[i] = x;
		}
		Z = new pair<int,pair<int,int>>[n];
		for(int i=0;i<n;i++)
		{
			Z[i].first = (int)((A[i].first)*10);
			Z[i].second.first = (int)((A[i].second.first)*10);
			Z[i].second.second = (int)((A[i].second.second)*10);
			//cout << Z[i].first << "," << Z[i].second.first << "," << Z[i].second.second << " ";
		}
		int* C=countingSort(Z,n).first;
		int k=countingSort(Z,n).second;
		for(int i=0;i<k;i++)
			output << C[i] << " ";
		for(int i=0;i<n;i++)
			output << "(" << (double)Z[i].first/10<< " " << (double)Z[i].second.first/10 << " " << (double)Z[i].second.second/10 << ") ";
		output << endl;
		
		delete[] A;
		delete[] B;
		delete[] C;
		delete[] D;
	}
	input.close();
	output.close();
	return 1;
}
