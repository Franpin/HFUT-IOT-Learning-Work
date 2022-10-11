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
		node **head,*visit;
		int i; 
		int floor;
		node *pre;
		node *p;
		tree(){
			i=0;
			floor=3;
			head=&a;	
		} 
		void create_tree(){
			if(floor==1){
				visit=a;
				*head=new node;
				(*head)->data=i;
				i++;	
				(*head)->lchild=NULL;
				(*head)->rchild=NULL;
			}
			else{	
			*head=new node;
			node **h=head;
			(*head)->data=i;
			i++;
			(*head)->lchild=NULL;
	 		(*head)->rchild=NULL;
			head=&((*head)->lchild);
			int b=floor;
			floor--;
			create_tree();
			head=&((*h)->rchild);
			floor=b;
			floor--;
			create_tree();
		}
	}
		void pre_order_traverse(){
			if(visit){
				cout<<visit->data<<endl;
				node* v=visit;
				visit=visit->lchild;
				pre_order_traverse();
				
				visit=v->rchild;
				pre_order_traverse();
			}
		} 
		void im_order_traverse(){
			if(visit){
				node* v=visit;
				visit=visit->lchild;
				im_order_traverse();
				
		
				if(!v->lchild)
					v->lchild=pre;
				if(!pre->rchild)
					pre->rchild=v;
				pre=v;	
				visit=v->rchild;
				im_order_traverse();
			}
		}
		void thread_tree(){
			p=new node;
			p->lchild=a;
			p->rchild=p;
			pre=p;
			im_order_traverse();
			pre->rchild=p;
			p->rchild=pre;
		}			
	
};
int main(){
	tree tree1;
	tree1.create_tree();
//	tree1.pre_order_traverse(); 
	tree1.thread_tree();
	cout<<tree1.p->rchild->lchild->lchild->data<<endl;
}
