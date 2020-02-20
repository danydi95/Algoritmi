#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/*//metodo ricorsivo per scrivere la parentesizzazione
void printRecursiveParentheses(vector<vector<int> > &input,int i,int j)
{
		if(i==j)
			cout << i;
		else
		{
			cout << "(";
			printRecursiveParentheses(input, input[i][j], j);
			cout << "x";
			printRecursiveParentheses(input, i, input[i][j] + 1);
			cout << ")";
		}
}

//metodo che semplifica la scrittura del metodo ricorsivo togliendo i e j come parametri da passare
void printRecursiveParentheses(vector<vector<int> > &input)
{
	if(input.size()>1)
		 printRecursiveParentheses(input, input.size() - 1, 0);
}*/

//metodo per calcolare la parentesizzazione delle matrici
int matrixChainMultiplyLookUp(vector<int> p,vector<vector<int> > &m)
{
	//se il vettore da calcolare è fatto da meno di 2 matrici allora non ha senso calcolare la parentesizzazione
	if(p.size()<2)
		return -1;
		
	int n=p.size()-1;
	
	m=vector<vector<int> >(n, vector<int>(n,0));
	
	//Inizializzazione matrice m (usato se vogliamo usare un valore di guardia INT_MAX per il confronto invece di tutti 0)
	/*for(int i=0;i<m.size();i++)
		for(int j=0;j<m.size();j++)
		{
			if(i=j)
				m[i][j]=0;
			else if(i<j)
				m[i][j]= INT_MAX;
		}*/
		
	//Calcolo
	//scorro per lunghezza della sequenza (diagonale)
	for(int len=1;len<n;len++)
	{
		for(int i=0;i<n-len;i++)
		{
			int j=i+len;
			for(int k=i;k<j;k++)
			{
				int c=m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1]; //calcolo costo
				if(m[i][j]==0 || c<m[i][j]) //se non è mai sta inserito o se è stato assegnato ed è più piccolo di quello precedentemenete calcolato
				{
					m[i][j]=c; //lo metto
					m[j][i]=k; //e memorizzo k nella diagonale inferiore
				}
			}
		}
	}
	return m[0][n-1];
}



int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	vector<int> v;
	while(getline(input,line))
	{
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while(getline(substring,token,' '))
			tokens.push_back(token);
		int n=stoi(tokens[0]);
		v.clear();
		for(int i=0;i<n;i++)
		{
			string value=tokens[i+1];
			string s1=value.erase(0,1);
			int j=1;
			while(j<s1.length() && s1.at(j)!='x') j++;
			s1.erase(j,s1.length());
			v.push_back(stoi(s1));
		}
		string s=tokens[n];
		int j=0; while(j<s.length() && s.at(j)!='x') j++;
		s.erase(0,j+1);
		s.erase(s.length()-1,s.length());
		v.push_back(stoi(s));
		
		vector<vector<int>> lookUpTable;	
		int operations= matrixChainMultiplyLookUp(v, lookUpTable);
		output << operations << endl;		
	}
	input.close();
	output.close();	
	return 1;
}
