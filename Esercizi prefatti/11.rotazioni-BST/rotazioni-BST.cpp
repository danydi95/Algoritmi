#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <class T> class Nodo
{
	private:
		T key;
		Nodo<T> *left,*right,*parent;
		int depth;
	public:
		Nodo(T key)
		{
			this->key=key;
			left=right=parent=NULL;
			depth=0;
		}
		
		T getKey() {return key;	}
		Nodo<T>* getLeft() {return left;}
		Nodo<T>* getRight() {return right;}
		Nodo<T>* getParent() {return parent;}
		void setLeft(Nodo<T>* left) {this->left=left;}
		void setRight(Nodo<T>* right) {this->right=right;}
		void setParent(Nodo<T>* parent) {this->parent=parent;}
		void setKey(T key) {this->key=key;}
		void setDepth(int x) {depth=x;}
		int getDepth() {return depth;}
};

template <class T> class BST
{
	private:
		Nodo<T>* root;
		int size;
		int isLeftChild(Nodo<T>* x)
		{
			return x==x->getParent()->getLeft();
		}		
	public:
		BST() {root=NULL;size=0;}
		
		void setRoot(Nodo<T>* x)
		{
			root=x;
		}
		
		Nodo<T>* getRoot()
		{
			return root;
		}
			
		void rightRotate(T key)
		{
			Nodo<T>* x = searchKey(key);
			Nodo<T>* y;
			if(x==NULL) return;	
								
			if (x->getLeft()==NULL) return;
			else
			{
			    y = x->getLeft();
			    x->setLeft(y->getRight());
			}
			if (y->getRight()!=NULL)
			    y->getRight()->setParent(x);

			y->setParent(x->getParent());
			
			if(x->getParent()==NULL){
			    root=y;
			}
			else if( x->getParent()->getRight() == x)
			{
			    x->getParent()->setRight(y);
			}
			else
			{
			    x->getParent()->setLeft(y);
			}
			y->setRight(x);
			x->setParent(y); 
		}
		
		void leftRotate(T key)
		{
			Nodo<T>* x = searchKey(key);
			Nodo<T>* y;
			if(x==NULL) return;	
								
			if (x->getRight()==NULL) return;
			else
			{
			    y = x->getRight();
			    x->setRight(y->getLeft());
			}
			if (y->getLeft()!=NULL)
			    y->getLeft()->setParent(x);

			y->setParent(x->getParent());
			
			if(x->getParent()==NULL){
			    root=y;
			}
			else if( x->getParent()->getLeft() == x)
			{
			    x->getParent()->setLeft(y);
			}
			else
			{
			    x->getParent()->setRight(y);
			}
			y->setLeft(x);
			x->setParent(y); 
		}
		
		
		Nodo<T>* searchKey(T key)
		{
			Nodo<T>* x=root;
			while((x!=NULL) && (key!=x->getKey()))
			{
				if(key<x->getKey()) x=x->getLeft();
				else x=x->getRight();
			}
			return x;
		}
		
		BST<T>* insert(T key)
		{
			Nodo<T>* x=root, *y=NULL;
			while(x!=NULL)
			{
				y=x;
				if(key<x->getKey()) x=x->getLeft();
				else x=x->getRight();
			}
			Nodo<T>* nuovo = new Nodo<T>(key);
			nuovo->setParent(y);
			if(y==NULL)
			{
				root=nuovo;
				root->setDepth(0);
			}
			else if(key<y->getKey()) y->setLeft(nuovo);
			else y->setRight(nuovo);
			size++;
			if(y!=NULL)
				nuovo->setDepth((nuovo->getParent()->getDepth())+1);
			return this;
		}
		
		void Trapianta(Nodo<T>* u,Nodo<T>* v)
		{
			if(u->getParent()==NULL) root=v;
			else if(u==u->getParent()->getLeft())
				u->getParent()->setLeft(v);
			else
				u->getParent()->setRight(v);
				
			if(v!=NULL)
				v->setParent(u->getParent());
		}
		
		Nodo<T>* Minimo(Nodo<T>* p)
		{
			Nodo<T>* x=p;
			while(x->getLeft()!=NULL) x=x->getLeft();
			return x;
		}
		
		BST<T>* del(T x)
		{
			Nodo<T>* y=NULL;
			Nodo<T>* z=searchKey(x);
			
			if(z->getLeft()==NULL) Trapianta(z,z->getRight());
			else if(z->getRight()==NULL) Trapianta(z,z->getLeft());
			else
			{
				y=Minimo(z->getRight());
				
				if(y->getParent()!=z)
				{
					Trapianta(y,y->getRight());
					y->setRight(z->getRight());
					y->getRight()->setParent(y);
				}
				Trapianta(z,y);
				y->setLeft(z->getLeft());
				y->getLeft()->setParent(y);
			}
			
			delete z;
			size--;
			return this;
		}
		void postorder(Nodo<T>* p,int level,char type,ofstream& output)
		{
			if(p!=NULL)
			{
				postorder(p->getLeft(),level,type,output);
				postorder(p->getRight(),level,type,output);
				if((level==-1)|| ((p->getDepth())==level))
				{
					double val = p->getKey();
					if(type=='c')
						output << (char)val << " ";
					else if (type == 'd')
						output << val << " ";
					else
						output << (int)val << " ";		
				}
			}
		}
		
		void postorderPrint(char type,ofstream& output)
		{
			postorder(root,-1,type,output);
			output << endl;
		}
		
		void inorder(Nodo<T>* p,int level,char type,ofstream& output)
		{
			if(p!=NULL)
			{
				inorder(p->getLeft(),level,type,output);
				if((level==-1)|| ((p->getDepth())==level))
				{
					double val = p->getKey();
					if(type=='c')
						output << (char)val << " ";
					else if (type == 'd')
						output << val << " ";
					else
						output << (int)val << " ";		
				}
				inorder(p->getRight(),level,type,output);
			}
		}
		
		void inorderPrint(char type,ofstream& output)
		{
			inorder(root,-1,type,output);
			output << endl;
		}
		
		void preorder(Nodo<T>* p,int level,char type,ofstream& output)
		{
			if(p!=NULL)
			{
				if((level==-1)|| ((p->getDepth())==level))
				{
					double val = p->getKey();
					if(type=='c')
						output << (char)val << " ";
					else if (type == 'd')
						output << val << " ";
					else
						output << (int)val << " ";		
				}
				preorder(p->getLeft(),level,type,output);
				preorder(p->getRight(),level,type,output);
			}
		}
		
		void preorderPrint(char type,ofstream& output)
		{
			preorder(root,-1,type,output);
			output << endl;
		}	
};


int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	BST<double>* tree;
	while(getline(input,line))
	{
		int operations=0;
		vector<string> tokens;
		stringstream substring(line);
		string token;
		double** A;
		while(getline(substring,token,' '))
		{
			tokens.push_back(token);
		}
		operations=stoi(tokens[1]);
		char type=tokens[0].at(0);
		int rotations=stoi(tokens[2]);
		string order = tokens[3];
		A = new double*[operations];
		tree = new BST<double>();
		for(int i=0;i<operations+rotations;i++)
		{
			string value = tokens[i+4];
			if(value.at(0)=='i') //inserimento
			{
				string s=value.erase(0,4);
				double d = stod(s);
				tree->insert(d);
			}
			else if(value.at(0)=='l')
			{
				string s=value.erase(0,5);
				double d = stod(s);
				tree->leftRotate(d);
			}
			else if(value.at(0)=='r')
			{
				string s=value.erase(0,6);
				double d = stod(s);
				tree->rightRotate(d);
			}
			else if(value.at(0)=='c')
			{
				string s=value.erase(0,5);
				double d = (type=='c') ? (s[0]) : stod(s);
				tree->del(d);
			}
		}
		if(order=="postorder")
			tree->postorderPrint(type,output);
		else if(order=="inorder")
			tree->inorderPrint(type,output);
		else if(order=="preorder")
			tree->preorderPrint(type,output);
		
		delete[] tree;
	}
	input.close();;
	output.close();
	return 1;
}
