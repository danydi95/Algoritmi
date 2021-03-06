#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <class T> class MaxBinaryHeap
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
			return ((*a)-*(b));
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
		MaxBinaryHeap(int size)
		{
			queue = new T*[size+1];
			queuesize=size+1;
			heapsize=0;
		}
		
		MaxBinaryHeap(T** v,int size)
		{
			queue=v;
			queuesize=size+1;
			heapsize=size;
		}
		
		MaxBinaryHeap<T>* enqueue(T key)
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
		
		T* extract(int& count)
		{
			if(heapsize==0) return NULL;
			swap(1,heapsize);
			heapsize--;
			heapify(1,count);
			return queue[heapsize+1];
		}
		
		void buildHeap(int& count)
		{
			for(int i=heapsize/2;i>0;i--)
				heapify(i,count);
		}
		
		void print(char type,ofstream& output, int &count)
		{
			output << count << " ";
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
	double** A;
	MaxBinaryHeap<double>* heap;
	while(getline(input,line))
	{
		int count=0;
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while(getline(substring,token,' '))
			tokens.push_back(token);
		char type=tokens[0].at(0);
		int n=stoi(tokens[1]);
		A = new double*[n+1];
		for(int i=1;i<=n;i++)
		{
			string value=tokens[i+1];
			double d = (type=='c') ? (value[0]) : stod(value);
			A[i]=new double(d);
		}
		heap=new MaxBinaryHeap<double>(A,n);
		heap->buildHeap(count);
		for(int i=0;i<n;i++)
			heap->extract(count);
		output << count << endl;
		count=0;
		delete heap;
		delete[] A;
	}
	input.close();;
	output.close();
	return 1;
}
