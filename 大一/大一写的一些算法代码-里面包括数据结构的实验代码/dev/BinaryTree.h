#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "OrderBinaryTree.h" 
#include <iostream>
#include <queue> 
//#include "BinaryTree.h" 
using namespace std;
struct node{
	node* lchild;
	node* rchild; 
	int data;
}; 
class BinaryTree
{
	public:
		BinaryTree(int *a);
		BinaryTree(OrderBinaryTree obt);
		BinaryTree(BinaryTree& bt);
		~BinaryTree();
		void create_Tree(int *a,node* &ptr); 
		void create_Tree2(int *Tree,node * &ptr,int i);
		void create_Tree3(node* ptr1,node* &ptr2); 
		void pre_find(node* ptr);
		void mid_find(node* ptr);
		void back_find(node* ptr);
		void layer_find();
		void mid_output(node* ptr,int layer);
		int set_attribute(node *ptr);
		void get_attribute();
		void find_node(node *ptr,int x);
		void get_layer(node* ptr,int x,int i,int &layer); 
		void swap_child(node *ptr); 
		void Print_Path(node *ptr,int i); 
		int find_path(node *ptr,int i,int *Path,int x,int &k);
		void closest_path(); 
		int max(int a,int b);
		int leaf_number;
		int height;
		int two_node;
		int Path[100]={0};
		int Path2[100]={0}; 
		int common_path[100]={0};
		node *root;
		int i;
		int t;
	protected:
};
BinaryTree::BinaryTree(int *a)
{
	root=NULL; 
	i=0;
	height=0;
	two_node=0;
	leaf_number=0;
	create_Tree(a,root);
}
BinaryTree::BinaryTree(OrderBinaryTree obt){
	root=NULL; 
	height=0;
	two_node=0;
	leaf_number=0;
	create_Tree2(obt.Tree,root,1); 
}
BinaryTree::BinaryTree(BinaryTree &bt){
	root=NULL; 
	height=0;
	two_node=0;
	leaf_number=0;
	create_Tree3(bt.root,this->root); 
} 
void BinaryTree::create_Tree2(int *Tree,node* &ptr,int i){
	if(Tree[i]!=0){
		node* new_node=new node;
		new_node->data=Tree[i];
		new_node->lchild=NULL;
		new_node->rchild=NULL;
		ptr=new_node;
		create_Tree2(Tree,ptr->lchild,2*i);
		create_Tree2(Tree,ptr->rchild,2*i+1);
	}	
}
void BinaryTree::create_Tree3(node* ptr1,node *&ptr2){
	if(ptr1!=NULL){
		node *new_node=new node; 
		new_node->data=ptr1->data;
		new_node->lchild=NULL;
		new_node->rchild=NULL;
		ptr2=new_node;
		create_Tree3(ptr1->lchild,ptr2->lchild);
		create_Tree3(ptr1->rchild,ptr2->rchild); 
	}
} 
BinaryTree::~BinaryTree()
{
}
void BinaryTree::pre_find(node *ptr){
	if(ptr!=NULL){
		cout<<ptr->data;
		pre_find(ptr->lchild);
		pre_find(ptr->rchild);		
	}	
}
void BinaryTree::mid_find(node *ptr){
	if(ptr!=NULL){
		mid_find(ptr->lchild);
		cout<<ptr->data;
		mid_find(ptr->rchild);		
	}	
}
void BinaryTree::back_find(node *ptr){
	if(ptr!=NULL){
		back_find(ptr->lchild);
		back_find(ptr->rchild);		
		cout<<ptr->data;
	}	
}
void BinaryTree::layer_find(){
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		node *ptr=q.front();
		q.pop();
		cout<<ptr->data; 
		if(ptr->lchild!=NULL){
			q.push(ptr->lchild);
		}
		if(ptr->rchild!=NULL){
			q.push(ptr->rchild);
		} 
	}
	
} 
void BinaryTree::mid_output(node *ptr,int layer){
	if(ptr!=NULL){
		mid_output(ptr->lchild,layer+1);
		cout<<layer<<"层 "<<"结点值为："<<ptr->data<<endl;
		mid_output(ptr->rchild,layer+1);		
	}		
} 
void BinaryTree::create_Tree(int* a,node* &ptr){
	if(a[i]!=0){
		node* new_node=new node;
		new_node->data=a[i];
		new_node->lchild=NULL;
		new_node->rchild=NULL;
		ptr=new_node;
		i++;
		create_Tree(a,ptr->lchild); 
		create_Tree(a,ptr->rchild);
	}
	else{
		i++; 
	} 
}
int BinaryTree::max(int a,int b){
	if(a>b){
		return a;
	} 
	else{
		return b;
	}	
}
int BinaryTree::set_attribute(node* ptr){
	if(ptr!=NULL){
		if(ptr->lchild!=NULL&&ptr->rchild!=NULL){
			two_node++;
		}
		if(ptr->lchild==NULL&&ptr->rchild==NULL){
			leaf_number++;
		}
		return max(set_attribute(ptr->lchild),set_attribute(ptr->rchild))+1;		
	}	
	else{
		return 0;
	}
} 
void BinaryTree::get_attribute(){
	height=set_attribute(root);
	cout<<"树高度为："<<height<<endl;
	cout<<"度为二的结点数为："<<two_node<<endl;
	cout<<"叶子结点数为："<<leaf_number<<endl; 
} 
void BinaryTree::find_node(node *ptr,int x){
	if(ptr==root&&ptr->data==x){
		cout<<"没有父结点！"<<endl;
		cout<<"没有兄弟结点！"<<endl; 
		if(ptr->lchild!=NULL){
			cout<<"左孩子结点为:"<<ptr->lchild->data<<endl;
				 
		}
		else{
			cout<<"没有左孩子结点"<<endl;
		} 
		if(ptr->rchild!=NULL){
			cout<<"右孩子结点为:"<<ptr->rchild->data<<endl;
				 
		}
		else{
			cout<<"没有右孩子结点"<<endl;
		} 
	}
	if(ptr->lchild!=NULL){
		if(ptr->lchild->data==x){
			cout<<"父节点为："<<ptr->data<<endl; 
			if(ptr->rchild!=NULL){
				cout<<"右兄弟结点为："<<ptr->rchild->data<<endl; 
			}
			else{
				cout<<"没有兄弟结点!"<<endl; 
			}
			if(ptr->lchild->lchild!=NULL){
				cout<<"左孩子结点为:"<<ptr->lchild->lchild->data<<endl;
				 
			}
			else{
				cout<<"没有左孩子结点"<<endl;
			} 
			if(ptr->lchild->rchild!=NULL){
				cout<<"右孩子结点为:"<<ptr->lchild->rchild->data<<endl;
				 
			}
			else{
				cout<<"没有右孩子结点"<<endl;
			} 
		}
		else{
			find_node(ptr->lchild,x);
		}
	
	}
	if(ptr->rchild!=NULL){
		 
		 if(ptr->rchild->data==x){
			cout<<"父节点为："<<ptr->data<<endl; 
			if(ptr->lchild!=NULL){
				cout<<"左兄弟结点为："<<ptr->lchild->data<<endl; 
			}
			else{
				cout<<"没有兄弟结点!"<<endl; 
			}
			if(ptr->rchild->lchild!=NULL){
				cout<<"左孩子结点为:"<<ptr->lchild->lchild->data<<endl;
				 
			}
			else{
				cout<<"没有左孩子结点"<<endl;
			} 
			if(ptr->rchild->rchild!=NULL){
				cout<<"右孩子结点为:"<<ptr->rchild->rchild->data<<endl;
				 
			}
			else{
				cout<<"没有右孩子结点"<<endl;
			} 
		}
		else{
			find_node(ptr->rchild,x);
		}		
		
	} 
} 
void BinaryTree::get_layer(node *ptr,int x,int i,int &layer){
	if(ptr!=NULL){
		i++;
		if(ptr->data==x){
			layer=i;
		}
		get_layer(ptr->lchild,x,i,layer);
		get_layer(ptr->rchild,x,i,layer);
	} 

}
void BinaryTree::swap_child(node *ptr){
	node* lchild=ptr->lchild;
	node* rchild=ptr->rchild;
	ptr->lchild=rchild;
	ptr->rchild=lchild;
	if(rchild!=NULL){
		swap_child(ptr->lchild);
	}
	if(lchild!=NULL){
		swap_child(ptr->rchild);
	}
} 
void BinaryTree::Print_Path(node* ptr,int i){
	if(ptr!=NULL){
		Path[i]=ptr->data;
		Print_Path(ptr->lchild,i+1); 
		Print_Path(ptr->rchild,i+1);
		if(ptr->lchild==NULL&&ptr->rchild==NULL){
			if(i==height-1){
				cout<<"最长路径：";
			}
			for(int j=i;j>=0;j--){	 
				cout<<Path[j];
			}
			cout<<endl;
		}
	}	
} 
int BinaryTree::find_path(node *ptr,int i,int *Path,int x,int &k){
	if(ptr!=NULL){
		Path[i]=ptr->data;
		if(ptr->data==x){
			k=i; 
			return 1;
		}
		if(find_path(ptr->lchild,i+1,Path,x,k)){
			return 1;	
		}
		if(find_path(ptr->rchild,i+1,Path,x,k)){
			return 1;
		}
	}
	return 0;
}
void BinaryTree::closest_path(){
	int i=0,j=0; 
	int *Path1=new int[height];
	int *Path2=new int[height];
	find_path(root,0,Path1,7,i);
	find_path(root,0,Path2,5,j);
	for(int a=i;a>=0;a--){
		for(int b=j;b>=0;b--){
			if(Path1[a]==Path2[b]){
				cout<<"共同祖先为："<<Path1[a]<<endl;
				return;
			}	 
		}
	}
}
#endif
