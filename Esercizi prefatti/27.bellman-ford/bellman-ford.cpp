#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <math.h>

using namespace std;

//classe per il rappresentare il grafo
template <class H,class T> class Graph
{
	private:
		int maxLenght, node_number, edge_number; //massimo numero nodi, numero di nodi attuale, numero di archi attuale
		H** keyMap; //mappa delle chiavi
		T** weightMatrix; //matrice dei pesi
		int** indexMatrix; //matrice degli indici
		int rootindex; //indice del nodo radice
		
		//metodo interno che modifica un arco del grafo
		Graph<H, T>* modifyEdge(H const& x, H const& y, T const& _weight, int ind)
		{
			int i= findIndex(x);
			int j= findIndex(y);
			if(i<0 || j<0)
				return this;
			if(indexMatrix[i][j]==ind)
			{
				if(ind)
				{
					indexMatrix[i][j]=0;
					edge_number--;
				}
				else
				{
					indexMatrix[i][j]=1;
					edge_number++;
				}
				weightMatrix[i][j]=_weight;
			}
			return this;
		}
		
	public:
		//costruttore che inizializza tutto
		Graph(int _maxLenght)
		{
			this->maxLenght=_maxLenght;
			indexMatrix = new int*[maxLenght];
			weightMatrix = new T*[maxLenght];
			edge_number=node_number=0;
			rootindex=-1;
			for(int i=0;i<maxLenght;i++)
			{
				indexMatrix[i]=new int[maxLenght];
				weightMatrix[i]= new T[maxLenght];
				for(int j=0;j<maxLenght;j++)
				{
					indexMatrix[i][j]=0;
					weightMatrix[i][j]=NULL;
				}
			}
			keyMap = new H*[maxLenght];
			for(int i=0;i<maxLenght;i++)
				keyMap[i]=NULL;
		}
		
		//metodo per trovare l'indice dalla chiave
		int findIndex(H x)
		{
			for(int i=0;i<node_number;i++)
				if(*keyMap[i]==x)
					return i;
			return -1;
		}
		
		//metodo che ritorna l'indice della radice
		int getRootIndex()
		{
			return this->rootindex;
		}
		
		int getMaxNodeNumber()
		{
			return maxLenght;
		}
		
		int getCurrentNodeNumber()
		{
			return node_number;
		}
		
		int getCurrentEdgeNumber()
		{
			return edge_number;
		}
		
		H** getGraphKeyMatrix()
		{
			return keyMap;
		}
		
		T** getWeightMatrix()
		{
			return weightMatrix;
		}
		
		int** getGraphIndexMatrix() 
		{
			return indexMatrix;
		}
		
		//metodo che da la chiave dall'indice
		H* getKey(int index)
		{
			if(index<0||index>=node_number)
				return NULL;
			return keyMap[index];
		}
		
		//metodo che aggiunge un nodo al grafo
		Graph<H,T>* addNode(H const& k)
		{
			if(node_number==maxLenght)
				return this;
			if(findIndex(k)>=0)
				return this;
			keyMap[node_number]=new H(k);
			node_number++;
			return this;
		}
		
		//metodo che aggiunge un nodo radice
		Graph<H,T>* addRootNode(H const& k)
		{
			rootindex=node_number;
			return addNode(k);
		}
		
		//metodo che aggiunge un arco
		Graph<H,T>* addEdge(H const& x, H const& y, T const& weight)
		{
			return this->modifyEdge(x,y,weight,0);
		}
		
		//metodo che cancella un arco
		Graph<H,T>* deleteEdge(H const& x,H const& y)
		{
			return this->modifyEdge(x,y,NULL,1);
		}
		
		//metodo che cancella un nodo
		Graph<H,T>* deleteNode(H const& key)
		{
			int pos=findIndex(key);
			if (pos < 0 || node_number == 0 || pos == rootindex)
				return this;
			for(int i=pos;i<node_number-1;i++)
				for(int j=0;j<node_number-1;j++)
				{
					indexMatrix[j][i]=indexMatrix[j][i+1]; //shift della colonna a destra
					weightMatrix[j][i]=weightMatrix[j][i+1]; //shift della colonna a destra
				}
			for(int i=pos;i<=node_number-2;i++)
				for(int j=0;j<=node_number-2;j++)
				{
					indexMatrix[i][j]=indexMatrix[i+1][j]; //shift della riga a destra
					weightMatrix[i][j]=weightMatrix[i+1][j]; //shift della riga a destra
				}
			for(int i=0;i<node_number;i++) //resettare l'ultima colonna
			{
				indexMatrix[i][node_number-1]=0;
				indexMatrix[node_number-1][i]=0;
				weightMatrix[i][node_number-1]=NULL;
				weightMatrix[node_number-1][i]=NULL;
			}	
			for(int j=pos;j<node_number-1;j++)
				keyMap[j]=keyMap[j+1];
			keyMap[node_number-1]=NULL;
			node_number--;
			return this;
		}
		
		//metodo che ritorna il nodo radice
		H const* getRootNode()
		{
			if(rootindex<0)
				return NULL;
			return keyMap[rootindex];
		}
		
		//metodo che setta il nodo radice
		void setRootNode(H const& k)
		{
			int t=findIndex(k);
			if(t<0)
				return;
			else rootindex=t;
		}
		
		//metodo ches tampa il grafo
		void print() const
		{
			for(int i=0;i<node_number;i++)
			{
				cout << "(" << i << ", " << *keyMap[i] << ")" << "--> ";
				for(int j=0;j<node_number;j++)
					if(indexMatrix[i][j])
						cout << "{" << *keyMap[j] << "," << weightMatrix[i][j] << "} ";
				cout << endl;
			}
		}
		
		//metodo che stampa la matrice degli indici
		void printIndexMatrix() const
		{
			for(int i=0;i<node_number;i++)
			{
				for(int j=0;j<node_number;j++)
					cout << indexMatrix[i][j] << " ";
				cout << endl;
			}
		}
		
		//metodo che stampa la matrice dei pesi
		void printWeightMatrix() const
		{
			for (int i = 0; i < node_number; i++)
			{
				for (int j = 0; j < node_number; j++)
					cout << weightMatrix[i][j] << " ";
				cout << endl;
			}
		}	
};

//algoritmo di bellman ford
template <class H, class T> int BellmanFord(Graph<H,T>* graph, H keysrc, T*& distances, int*& predecessors)
{
	int V = graph->getCurrentNodeNumber();
	distances=new T[V];
	predecessors = new int[V];
	int src = graph->findIndex(keysrc);
	//Inizialmente la distanza è lontana per ogni nodo //gestisco l'uso della flag
	for(int i=0;i<V;i++)
	{
		distances[i]=INT_MAX;
		predecessors[i]=-1;
	}
	distances[src]=0;
	predecessors[src]=src;
	//Rilassiamo tutti gli archi |V|-1 volte
	for(int s=0;s<V-1;s++)
		for(int i=0;i<V;i++)
			for(int j=0;j<V;j++)
			{
				if(distances[i]!=INT_MAX && graph->getGraphIndexMatrix()[i][j]==1)
				{
					T weight = graph->getWeightMatrix()[i][j];
					if(distances[i]+weight<distances[j])
					{
						distances[j]=distances[i]+weight;
						predecessors[j]=i;
						//cout << j << " " << i << endl;
					}
				}
			}
	//Check per cicli negativi
	//(praticamente se dopo aver rilassato gli archi V-1 volte
	//ci sono ancora archi da rilassare allora c'è un ciclo negativo in corso)
	for(int i=0;i<V;i++)
		for(int j=0;j<V;j++)
		{
			if(distances[i]!=INT_MAX && graph->getGraphIndexMatrix()[i][j]==1)
			{
				T weight = graph->getWeightMatrix()[i][j];
				if(distances[i]+weight<distances[j])
					return 0;
			}
		}
	return 1;
}

template <class H,class T> int DistancesTo(Graph<H,T>* graph, H src, H des, T* distances, int* predecessors)
{
	if(predecessors==NULL || graph->findIndex(src)<0)
		return 0;
	if(distances==NULL)
		return 0;
	int source = graph->findIndex(src);
	int dest = graph->findIndex(des);
	return distances[dest];
}

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	Graph<double,double>* g;
	while(getline(input,line))
	{
		string token;
		stringstream substring(line);
		vector<string> tokens;
		while(getline(substring,token,' '))
			tokens.push_back(token);
		int nodes=stoi(tokens[0]);
		int edges=stoi(tokens[1]);
		double start_node=stod(tokens[nodes+edges*3+3]);
		double end_node=stod(tokens[nodes+edges*3+4]);
		g = new Graph<double,double>(nodes);
		for(int i=0;i<nodes;i++)
		{
			double d = stod(tokens[i+3]);
			g->addNode(d);
		}
		double *a = new double[edges];
		double *b = new double[edges];
		double *c = new double[edges];
		for(int i=0,j=0;i<edges*3,j<edges;i++)
		{
			string value=tokens[nodes+3+i];
			if(value.at(0)=='(')
			{
				double d = stod(value.erase(0,1));
				//cout << "Inserisco il primo elem: " << d << " in pos " << j << endl;
				a[j]=d;
			}
			else if(value.back()==')')
			{
				double d = stod(value.erase(value.length()-1,value.length()));
				//cout << "Inserisco il terzo elem: " << d << " in pos " << j << endl;
				c[j]=d;
				j++;
			}
			else
			{
				double d = stod(value);
			//	cout << "Inserisco il secondo elem: " << d << " in pos " << j << endl;
				b[j]=d;
			}
			
		}
		for(int i=0;i<edges;i++)
		{
		//	cout << "Aggiungo arco: " << a[i] << "," << b[i] << "," << c[i] << endl;
			g->addEdge(a[i],b[i],c[i]);
		}
		
		double *distances=NULL;
		int *predecessors=NULL;
		if(BellmanFord(g,start_node,distances,predecessors))
		{
			if(DistancesTo(g,start_node,end_node,distances,predecessors)==INT_MAX)
				output << "inf.\n";
			else
				output << DistancesTo(g,start_node,end_node,distances,predecessors) << endl;
		}
		else
			output << "undef.\n";
		delete g,a,b,c;
	}
	input.close();
	output.close();
	return 1;
}
