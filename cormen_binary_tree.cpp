#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>


using namespace std;
struct node
{
  int key;
	node* left;
	node* right;
	node* parent;
};
node *root=new node;

node *create_node(int e)
{
	
 	node *p=new node;
	p->key=e;
	p->left=NULL;
	p->right=NULL;
	
	return p;
}
void insert_bst(node *t,node *temp)
{
	node *travel;
	travel=t;
	if(travel->left==NULL&&travel->right==NULL)
	{
		if(travel->key>temp->key)
		{
			temp->parent=travel;
			travel->left=temp;
		}	

		else
		{	
			temp->parent=travel;
			travel->right=temp;
		}
	}
	else  
	{
		if(travel->left==NULL)
		{
			if(travel->key>temp->key)
			{
				temp->parent=travel;
				travel->left=temp;
			}	

			else
				insert_bst(travel->right,temp);
		}
		else
		{
			if(travel->right==NULL)
			{
				if(travel->key<temp->key)
				{
					temp->parent=travel;
					travel->right=temp;
				}
				else
				{	
					insert_bst(travel->left,temp);
				}
			}
			else
			{
				if(travel->key>temp->key)
					insert_bst(travel->left,temp);
				else
					insert_bst(travel->right,temp);
			}
		}
	}
}
int minimum(node *t)
{
	node *travel=new node;
	travel=t;
	int x;
	if(travel==NULL)
	{	return -1;}
	
	else if(travel->left==NULL)
	{
			
		x=travel->key;		return x;
	}
	else
	{	minimum(travel->left);}
}	
node* search(node *t,int n)
{
	node *travel=t;
	if(travel==NULL)
	{
		//cout<<"NIL";
		return  NULL;
	}
	else if(n==travel->key)
			return travel;
		else if(n<travel->key)
			return(search(travel->left,n));
			else
				return(search(travel->right,n));
}
void maximum(node *t)
{
	node *travel=new node;
	travel=t;
	if(travel==NULL)
		cout<<"NIL\n";
	else
	if(travel->right==NULL)
	{
			
			
		cout<<travel->key<<"\n";
	}
	else
		maximum(travel->right);
}

void successor(node *p)
{
	node *x=new node;
	x=p;
	node *temp;
	if(x->right!=NULL)
	{	cout<<minimum(x->right)<<"\n";}
	
	else
	{
		node *y=new node;
		y=x->parent;
		if(y==NULL)
			cout<<"NIL1\n";
		else
		{
			while(y!=NULL&&x==y->right)
			{
				x=y;
				y=y->parent;
			}
			if(y==NULL)
				cout<<"NIL2"<<"\n";			
			else		
				cout<<y->key<<"\n";
	
		}
	
	}	

}
void predeccessor(node *p)
{
	node *x=new node;
	x=p;
	if(x->left!=NULL)
		maximum(x->left);
	else
	{
		node *y=new node;
		y=x->parent;
		if(y==NULL)
			cout<<"NIL"<<"\n";
		else
		{
			while(y!=NULL&&x==y->left)
			{
				x=y;
				y=y->parent;
			}	
			if(y==NULL)
				cout<<"NIL1"<<"\n";			
			else		
				cout<<y->key<<"\n";
	
		}
	
	}	

}
void transplant(node *t,node *u,node* v)
{
	if(u->parent==NULL)
	{	
		if(v!=NULL)
		root=v;	
		else
		root==NULL;
	}
	else if(u==u->parent->left)
		u->parent->left=v;
		else 
		{	u->parent->right=v;}
	if(v!=NULL)
		v->parent=u->parent;
}
void tree_delete(node *t,node *z)
{
	node *y=new node;
	
	
	if(z->left==NULL)
		transplant(t,z,z->right);
	else if(z->right==NULL)
		transplant(t,z,z->left);
		else
		{
			int l=minimum(z->right);
			y=search(t,l);
		
			
			if(y->parent!=z)
			{
				transplant(t,y,y->right);
				y->right=z->right;
				y->right->parent=y;
			}
			transplant(t,z,y);	
			y->left=z->left;
			y->left->parent=y;
		}
}
	
			
int main()
{
	int t;
	float element;
	ifstream fin;
	node *temp=new node;
	
	root=NULL;
	fin.open("out.txt",ios::in);
	while(!fin.eof())
	{
		fin>>t;
		switch(t)
		{
			case 0:
				exit(0);
			case 1:
				fin>>t;
				cout<<"\n";
				temp=create_node(t);
				//cout<<temp->key;
				if(root==NULL)
				{
					root=temp;
				}
				else
				insert_bst(root,temp);
				break;
			case 2:
				fin>>t;
				temp=search(root,t);
				if(temp==NULL)
				cout<<"NOT FOUND\n";
				else
				cout<<"FOUND\n";
				/*if(temp->key==t)
					cout<<"FOUND\n";
				else
					cout<<"NOT FOUND\n";	*/
				break;
			case 3:
				t=minimum(root);
				if(t==-1)	
					cout<<"NIL\n";
				else
					cout<<t<<"\n";
				break;
			case 4:
				maximum(root);
				break;
			case 5:
				fin>>t;
				temp=search(root,t);
				//cout<<temp->key;
				if(temp==NULL)
					cout<<"NOT FOUND\n";
				else
				if(temp->key==t)
					predeccessor(temp);
				else
					cout<<"NOT FOUND\n";
				break;			

			case 6:
				fin>>t;
				temp=search(root,t);
				//cout<<temp->key;
				if(temp==NULL)
					cout<<"NOT FOUND\n";
				else
				if(temp->key==t)
					successor(temp);
				else
					cout<<"NOT FOUND\n";
				break;
			case 7:
				fin>>t;
				cout<<"\n";
				if(root->left==NULL&&root->right==NULL)
					root=NULL;
				else
				{
			
					temp=search(root,t);
					if(temp->key==t)
						tree_delete(root,temp);
					else
						cout<<"NOT FOUND\n";
				}
		}
	}

	return 0;
}


