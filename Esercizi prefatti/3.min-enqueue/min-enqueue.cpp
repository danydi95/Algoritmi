#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

template <class T> class MinHeap
{
	private:
		T** queue;
		int heapsize;
		int queuesize;
		int left(int i) {return (i<<1);	}
		int right(int i) {return (i<<1)|1;	}
		int parent(int i) {return (i>>1);	}
		
		void swap(int i,int j)
		{
			T* tmp=queue[i];
			queue[i]=queue[j];
			queue[j]=tmp;
		}
		
		double compare(T* a,T* b)
		{
			return ((*b)-*(a));
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
		MinHeap(int size)
		{
			queue = new T*[size+1];
			queuesize=size+1;
			heapsize=0;
		}
		
		MinHeap<T>* enqueue(T key)
		{
			if(heapsize==queuesize-1) return this;
			heapsize++;
			queue[heapsize]=new T(key);
			int i=heapsize;
			while(i>1 && compare(queue[i],queue[parent(i)])>0)
			{
				swap(i,parent(i));
				i=parent(i);
			}
			return this;
		}
		
		void print(char type,ofstream& output)
		{
			if(heapsize<1) return;
			for(int i=1;i<=heapsize;i++)
			{
				double val = *(queue[i]);
				if(type=='c')
					output << (char)val;
				else if(type=='d')
					output << val;
				else
					output << (int)val;
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
	MinHeap<double>* heap;
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
		operations = stoi(tokens[1]);
		heap = new MinHeap<double>(operations+1);
		char type = tokens[0].at(0);
		for(int i=1;i<=operations;i++)
		{
			string value = tokens[i+1];
			double d = (type=='c') ? (value[0]) : stod(value);
			heap->enqueue(d);
		}
		heap->print(type,output);
		delete[] heap;
	}
	input.close();
	output.close();
	return 1;
}
