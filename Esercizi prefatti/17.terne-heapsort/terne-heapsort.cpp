#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <class T> class MinHeap
{
	private:
		T** queue;
		int queuesize;
		int heapsize;
		int left(int i) {return (i<<1);}
		int right(int i) {return (i<<1)|1;}
		int parent(int i) {return (i>>1);}
		
		double compare(T* a,T* b)
		{
			T x=*(a);
			T y=*(b);
			if(x.first<y.first) return -1;
			if(x.first>y.first) return 1;
			if(x.first==y.first)
			{
				if(x.second.first<y.second.first) return -1;
				if (x.second.first>y.second.first) return 1;
				if(x.second.first==y.second.first)
				{
					if(x.second.second<y.second.second) return -1;
					if(x.second.second>y.second.second) return 1;
					else return 0;
				}
			}
		}
		
		void swap(int i,int j)
		{
			T* aux=queue[i];
			queue[i]=queue[j];
			queue[j]=aux;
		}
		
		void heapify(int i,int& count)
		{
			if(i>heapsize) return;
			int l=left(i);
			int r=right(i);
			int max=i;
			if(l<=heapsize && compare(queue[max],queue[l])<0) max=l;
			if(r<=heapsize && compare(queue[max],queue[r])<0) max=r;
			count++;
			if(max==i) return;
			swap(i,max);
			heapify(max,count);
		}
	public:
		MinHeap(int size) {
			queue=new T*[size+1];
			heapsize=0;
			queuesize=size+1;
		}
		MinHeap(T** v,int size)
		{
			queue=v;
			queuesize=size+1;
			heapsize=size;
		}
		
		MinHeap<T>* enqueue(T key)
		{
			if(heapsize==queuesize-1) return this;
			heapsize++;
			queue[heapsize]= new T(key);
			int i=heapsize;
			while(i>1 && compare(queue[i],queue[parent(i)])>0)
			{
				swap(i,parent(i));
				i=parent(i);
			}
			return this;
		}
		
		void modify(int i,T k)
		{
			if(i<1 || i>heapsize) return;
			if(compare(queue[i],&k)>=0) return;
			queue[i]= new T(k);
			while(i>1 && compare(queue[i],queue[parent(i)])>0)
			{
				swap(i,parent(i));
				i=parent(i);
			}
			return;
		}
		
		void buildHeap(int& count)
		{
			for(int i=heapsize/2;i>0;i--)
				heapify(i,count);
		}
		
		T* extract(int& count)
		{
			if(heapsize==0) return NULL;
			swap(1,heapsize);
			heapsize--;
			heapify(1,count);
			return queue[heapsize+1];
		}
		
		void sort(int& count)
		{
			buildHeap(count);
			int n=heapsize;
			for(int i=0;i<n;i++) extract(count);
			heapsize=n;
		}
		
		void print(char type,ofstream& output, int &count)
		{
			output << count << " ";
			if(heapsize<1) return;
			for(int i=1;i<=heapsize;i++)
			{
				double val1 = queue[i]->first;
				double val2 = queue[i]->second.first;
				double val3 = queue[i]->second.second;
				if(type=='c')
					output << "(" << (char)val1 << " " << (char)val2 << " " << (char)val3 << ")";
				else if(type=='d')
					output << "(" << val1 << " " << val2 << " " << val3 << ")";
				else
					output << "(" << (int)val1 << " " << (int)val2 << " " << (int)val3 << ")";
				if(i!=heapsize)
					output << " ";	
			}
			output << endl;	
		}
		
};

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	MinHeap<pair<double,pair<double,double>>>* heap;
	pair<double,pair<double,double>> **A;
	double *B,*C,*D;
	while(getline(input,line))
	{
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while(getline(substring,token,' '))
			tokens.push_back(token);
		int count=0;
		char type=tokens[0].at(0);
		int n=stoi(tokens[1]);
		A = new pair<double,pair<double,double>>*[n+1];
		B = new double[n];
		C = new double[n];
		D = new double[n];
		int j=0,z=0,k=0;
		for(int i=0;i<3*n,j<n,k<n,z<n;i++)
		{
			string value=tokens[i+2];
			if(value.at(0)=='(')
			{
				string s1=value.erase(0,1);
				double d1 = (type=='c') ? s1[0] : stod(s1);
				B[j]=d1;
				//cout << "Inserisco " << B[j] << " in " << j << endl;
				j++;
			}
			else
			{
				if(value.at(value.length()-1)==')')
				{
					string s2=value.erase(value.length()-1,value.length());
					double d2 = (type=='c') ? s2[0] : stod(s2);
					C[z]=d2;
					//cout << "Inserisco " << C[z] << " in " << z << endl;
					z++;
				}
				else
				{
					double d3 = (type=='c') ? value[0] : stod(value);
					D[k]=d3;
					//cout << "Inserisco " << D[k] << " in " << k << endl;
					k++;
				}
			}
		}
		
		for(int i=0;i<n;i++)
		{
			pair<double,double> tmp = make_pair(D[i],C[i]);
			pair<double,pair<double,double>> x = make_pair(B[i],tmp);
			A[i+1]= new pair<double,pair<double,double>>(x);
			//cout << "(" << A[i+1]->first << " " << A[i+1]->second.first << " " << A[i+1]->second.second << ")" << endl;
		}
	 	heap = new MinHeap<pair<double,pair<double,double>>>(A,n);
		heap->sort(count);
		heap->print(type,output,count);
		count=0;	
		delete[] A;
		delete[] B;
		delete[] C;
		delete[] D;
		delete heap;
	}
	input.close();
	output.close();
	return 1;
}
