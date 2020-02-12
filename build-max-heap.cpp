#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

template <class T> class PriorityQueue
{
	private:
		T** queue;
		int heapsize;
		int queuesize;
		int left(int i) {return (i<<1);	}
		int right(int i) {return (i<<1)|1;}
		int parent(int i) {return (i>>1);}
		void swap(int i,int j)
		{
			T* tmp=queue[i];
			queue[i]=queue[j];
			queue[j]=tmp;
		}
		
		double compare(T* a,T* b)
		{
			return (double)(*(a)-*(b));
		}
		
		void heapify(int i)
		{
			if(i>heapsize) return;
			int l=left(i);
			int r=right(i);
			int max=i;
			if(l<=heapsize && compare(queue[max],queue[l])<0) max=l;
			if(r<=heapsize && compare(queue[max],queue[r])<0) max=r;
			if(max==i) return;
			swap(i,max);
			heapify(max);
		}
		
	public:
		PriorityQueue(int size)
		{
			queue=new T*[size+1];
			queuesize=size+1;
			heapsize=0;
		}
		
		PriorityQueue(T** v,int size)
		{
			queue=v;
			queuesize=size+1;
			heapsize=size;
		}
		
		void buildHeap()
		{
			for(int i=heapsize/2;i>0;i--)
				heapify(i);
		}
		
		void print(char type, ofstream& output)
		{
			if (heapsize<1)
				return;		
			for (int i = 1; i <= heapsize; i++)			
				{				
					double val = *(queue[i]);
					if (type == 'c')
						output << (char)val;
					else if (type == 'd')
						output << val;
					else
						output << (int)val;		
					if (i != heapsize)
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
	PriorityQueue<double>* heap;
	double** A;
	while (getline(input, line))
	{
		int operations = 0;
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while (getline(substring, token, ' '))
		{
			tokens.push_back(token);
		}
		operations = stoi(tokens[1]);
		A = new double*[operations+1];
		char type = tokens[0].at(0);
		for (int i = 1; i < operations+1; i++)
		{
			string value=tokens[i+1];
			double d = (type == 'c') ? (value[0]) : stod(value);
			A[i]= new double(d);
		}
		heap = new PriorityQueue<double>(A,operations);
		heap->buildHeap();
		heap->print(type,output);
		delete [] A;
		delete [] heap;
		
	}
	input.close();
	output.close();
	return 1;
}
