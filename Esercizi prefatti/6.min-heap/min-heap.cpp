#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <class T> class MinBinaryHeap
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
		MinBinaryHeap(int size)
		{
			queue = new T*[size+1];
			queuesize=size+1;
			heapsize=0;
		}
		
		MinBinaryHeap(T** v,int size)
		{
			queue=v;
			queuesize=size+1;
			heapsize=size;
		}
		
		MinBinaryHeap<T>* enqueue(T key)
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
	MinBinaryHeap<double>* heap;
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
		heap=new MinBinaryHeap<double>(n);
		for(int i=0;i<n;i++)
		{
			string value=tokens[i+2];
			if(value.at(1)==':')
			{
				string s=value.erase(0,2);
				double d = (type=='c') ? (s[0]) : stod(s);
				heap->enqueue(d);
			}
			else
				heap->extract(count);
		}
		heap->print(type,output,count);
		count=0;
		delete heap;
	}
	input.close();;
	output.close();
	return 1;
}
