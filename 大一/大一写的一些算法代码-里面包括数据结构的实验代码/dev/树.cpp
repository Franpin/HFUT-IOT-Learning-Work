#include<iostream>
using namespace std;
struct node{
	int data;
	node *lchild;
	node *rchild;
}; 
class tree{
	public:
		node *a;
		node *head;
		int i; 
		int floor;
		tree(){
			i=1;
			floor=4;
			a=new node;
			a->data=i;
			i++;
			head=a;
			
		} 
		void create_tree(){
			if(floor==1){
				head->lchild=NULL;
				head->rchild=NULL;
				cout<<head->data<<"."<<endl; 
			}
			else{
			cout<<head->data<<endl;
			node *left=new node;
			left->data=i;
			i++;
			node *right=new node;
			right->data=i;
			i++;
			head->lchild=left;
			head->rchild=right;
			head=left;
			int b=floor;
			floor--;
			create_tree();
			head=right;
			floor=b;
			floor--;
			create_tree();
		}
		}
};
int main(){
	tree tree1;
	tree1.create_tree();
	cout<<tree1.a->lchild->lchild->rchild->data<<endl;
}
