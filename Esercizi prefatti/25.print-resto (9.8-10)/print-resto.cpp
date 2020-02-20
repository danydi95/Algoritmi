#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#define min(A,B) A<B ? A : B

using namespace std;

pair<int*,int> minChange(int* coins,int n, int resto)
{
        int* count = new int[resto + 1];
        int* from = new int[resto + 1];
        count[0] = 1;
        for (int i = 0 ; i < resto; i++)
            if (count[i] > 0)
                for (int j = 0; j < n; j++)
                {
                    int p = i + coins[j];
                    if (p <= resto)
                    {
                        if (count[p] == 0 || count[p] > count[i] + 1)
                        {
                            count[p] = count[i] + 1;
                            from[p] = j;
                        }
                    }
                }
        int* result = new int[count[resto] - 1];
        int k = resto;
        while (k > 0)
        {
            result[count[k] - 2] = coins[from[k]];
            k = k - coins[from[k]];
        }
		pair<int*,int> x = make_pair(result,count[resto]-1);
        return x;
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
		int resto=stoi(tokens[0]);
		int ntagli=stoi(tokens[1]);
		int* tagli = new int[ntagli];
		for(int i=0;i<ntagli;i++)
			tagli[i]=stoi(tokens[i+2]);
		
		pair<int*,int> A=minChange(tagli,ntagli,resto);
		output << A.second << " ";
		for(int i=0;i<A.second;i++)
			output << A.first[i] << " ";
		output << endl;
	}
	input.close();
	output.close();
	return 1;
}
