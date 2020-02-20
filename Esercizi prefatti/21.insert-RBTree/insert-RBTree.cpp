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
		int color;
	public:
		Nodo(T key,int color)
		{
			this->key=key;
			left=right=parent=NULL;
			this->color=color;
		}
		Nodo<T>* getLeft() {return left;}
		Nodo<T>* getRight() {return right;}
		Nodo<T>* getParent() {return parent;}
		void setLeft(Nodo<T>* l) {left=l;}
		void setRight(Nodo<T>* r) {right=r;}
		void setParent(Nodo<T>* p) {parent=p;}
		T getKey() {return key;	}
		int getColor() {return color;}
		void setKey(T k) {key=k;}
		void setColor(int c) {color=c;}
};

template <class T> class RBTree
{
	private:
		Nodo<T>* root;
		const int RED=1;
		const int BLACK=0;
		
		int isLeftChild(Nodo<T>* x)
		{
			return x==x->getParent()->getLeft();
		}
		
		Nodo<T>* getUncle(Nodo<T>* x)
		{
			if(x->getParent()==NULL || x->getParent()->getParent()==NULL)
				return NULL;
			if(isLeftChild(x->getParent()))
				return x->getParent()->getParent()->getRight();
			else
				return x->getParent()->getParent()->getLeft();
		}
		
		void rightRotate(Nodo<T>* x)
		{
			if(x==NULL) return;	
			Nodo<T>* y=NULL;				
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
		
		void leftRotate(Nodo<T>* x)
		{
			if(x==NULL) return;	
			Nodo<T>* y=NULL;			
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
		
		void swapColors(Nodo<T>* n1,Nodo<T>* n2)
		{
			int temp=n1->getColor();
			n1->setColor(n2->getColor());
			n2->setColor(temp);
		}
		
		void insertFixUp(Nodo<T>* x)
		{
			if(x==root)
			{
				x->setColor(BLACK);
				return;
			}
			Nodo<T>* parent=x->getParent();
			Nodo<T>* grandparent=x->getParent()->getParent();
			Nodo<T>* uncle=getUncle(x);
			if(parent->getColor()!=BLACK)
			{
				if(uncle!=NULL && uncle->getColor()==RED)
				{
					parent->setColor(BLACK);
					uncle->setColor(BLACK);
					grandparent->setColor(RED);
					insertFixUp(grandparent);
				}
				else
				{
					if(isLeftChild(parent))
					{
						if(isLeftChild(x))
							swapColors(parent,grandparent);
						else
						{
							leftRotate(parent);
							swapColors(x,grandparent);
						}
						rightRotate(grandparent);
					}
					else
					{
						if(isLeftChild(x))
						{
							rightRotate(parent);
							swapColors(x,grandparent);
						}
						else	
							swapColors(parent,grandparent);
						leftRotate(grandparent);
					}
				}
			}
		}
		
		void inOrder(Nodo<T>* x, ofstream& out)
		{
			if(x==NULL) return;
			inOrder(x->getLeft(),out);
			out << "(" << x->getKey() << " ";
			if(x->getColor()==BLACK)
				out << "B) ";
			else
				out << "R) ";
			inOrder(x->getRight(),out);
		}
		
		void postOrder(Nodo<T>* x, ofstream& out)
		{
			if(x==NULL) return;
			postOrder(x->getLeft(),out);
			postOrder(x->getRight(),out);
			out << "(" << x->getKey() << " ";
			if(x->getColor()==BLACK)
				out << "B) ";
			else
				out << "R) ";
		}
		
		void preOrder(Nodo<T>* x,ofstream& out)
		{
			if(x==NULL) return;
			out << "(" << x->getKey() << " ";
			if(x->getColor()==BLACK)
				out << "B) ";
			else
				out << "R) ";
			preOrder(x->getLeft(),out);
			preOrder(x->getRight(),out);
		}
	public:
		RBTree() {root=NULL;}
		Nodo<T>* getRoot() {return root;}
		void setRoot(Nodo<T>* r) {root=r;}
		
				
		Nodo<T>* search(T key)
		{
			Nodo<T>* temp=root;
			while(temp != NULL && temp->getKey() != key)
			{
				if(key<temp->getKey())
				{
					if(temp->getLeft() != NULL)
						temp=temp->getLeft();
					else break;
				}
				else
				{
					if(temp->getRight() != NULL)
						temp=temp->getRight();
					else break;
				}
			}
			return temp;
		}
		
		RBTree<T>* insertKey(T key)
		{
			Nodo<T>* nuovo = new Nodo<T>(key,RED);
			if(root==NULL)
			{
				nuovo->setColor(BLACK);
				root=nuovo;
			}
			else
			{
				Nodo<T>* tmp=search(key);
				if(tmp->getKey()!=key)
				{
					nuovo->setParent(tmp);
					if(key<tmp->getKey())
						tmp->setLeft(nuovo);
					else
						tmp->setRight(nuovo);
					insertFixUp(nuovo);
				}
			}
			return this;
		}
		
		void printInOrder(ofstream& out)
		{
			inOrder(root,out);
			out << endl;
		}
		
		void printPostOrder(ofstream& out)
		{
			postOrder(root,out);
			out << endl;
		}
		
		void printPreOrder(ofstream& out)
		{
			preOrder(root,out);
			out << endl;
		}
		
};

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	RBTree<double>* tree;
	while(getline(input,line))
	{
		vector<string> tokens;
		stringstream substring(line);
		string token;
		while(getline(substring,token,' '))
			tokens.push_back(token);
		tree = new RBTree<double>();
		int n=stoi(tokens[1]);
		string order=tokens[2];
		for(int i=0;i<n;i++)
		{
			string value=tokens[i+3];
			double d = stod(tokens[i+3]);
			tree->insertKey(d);
		}
		if(order=="postorder")
			tree->printPostOrder(output);
		else if(order=="preorder")
			tree->printPreOrder(output);
		else
			tree->printInOrder(output);
				
		delete tree;
	}	
	input.close();
	output.close();
	return 1;
}
