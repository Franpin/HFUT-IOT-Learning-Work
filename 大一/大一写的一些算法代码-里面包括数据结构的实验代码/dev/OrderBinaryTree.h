#ifndef ORDERBINARYTREE_H
#define ORDERBINARYTREE_H
#include<iostream>
using namespace std; 
class OrderBinaryTree
{
	public:
		OrderBinaryTree(int *a);
	
		void Tree_create(int i,int *a); 
		int Tree[100]={0}; 
		int j;
	protected:
		
};
OrderBinaryTree::OrderBinaryTree(int *a)
{
	j=0;
	Tree_create(1,a); 
}
void OrderBinaryTree::Tree_create(int i,int *a){
	if(a[j]!=0){
		Tree[i]=a[j];
		j++;
		Tree_create(2*i,a);
		Tree_create(2*i+1,a);
	}
	else{
		j++;
	}
}
#endif
