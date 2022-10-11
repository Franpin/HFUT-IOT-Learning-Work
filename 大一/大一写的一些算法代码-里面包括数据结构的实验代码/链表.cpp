#include<iostream> 
using namespace std;
struct node{
	int data;
	node* next;
	node* pre;
};

int main(){
	node *head=NULL;
	node *p,*h;
	p=new node;
	p->pre=NULL;
	head=p;
	int i=0;
	while(i<=4){
		h=new node;
		h->pre=p;
		h->data=i;
		h->next=NULL; 
		p->next=h;
		p=h;
		i++;
	}
	while(p){
		cout<<p->data<<endl;
		p=p->pre;
	} 
	cout<<head->next->data<<endl;
	return 0;
}
