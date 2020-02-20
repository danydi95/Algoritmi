#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#define min(A,B) A<B ? A : B

using namespace std;

void sort(pair<int,int>* a,int n)
{
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
		{
			if(a[i].second>a[j].second)
			{
				int aux1=a[i].first;
				int aux2=a[i].second;
				a[i].first=a[j].first;
				a[i].second=a[j].second;
				a[j].first=aux1;
				a[j].second=aux2;		
			}
			else if(a[i].second==a[j].second)
			{
				if(a[i].first>a[j].first)
				{
					int aux1=a[i].first;
					int aux2=a[i].second;
					a[i].first=a[j].first;
					a[i].second=a[j].second;
					a[j].first=aux1;
					a[j].second=aux2;
				}
			}
		}
}

int activitySelector(int* s, int* f, int n) 
{
	pair<int,int>* A = new pair<int,int>[n];
	for(int i=0;i<n;i++)
	{
		A[i].first=s[i];
		A[i].second=f[i];
	}
	sort(A,n);
	int i=1;
	int count=A[i];
	for(int m=1;m<n;m++)
		if(A[m].first>=A[i].second)
			{
				count++;
				i=m;
			}
	return count;
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
		int n=stoi(tokens[0]);
		int* s = new int[n];
		int* f = new int[n];
		int j=0;
		for(int i=0;i<n,j<n;i++)
		{
			string value=tokens[i+1];
			if(i%2==0)
			{
				s[j]=stoi(value.erase(0,1));
				j++;
			}
		}
		j=0;
		for(int i=0;i<n,j<n;i++)
		{
			string value=tokens[i+1];
			if(i%2!=0)
			{
				f[j]=stoi(value.erase(value.length()-1,value.length()));
				j++;
			}
		}		
		output << activitySelector(s,f,n) << endl;
	}
	input.close();
	output.close();
	return 1;
}
