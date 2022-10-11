#include<iostream>
using namespace std;
struct node{
	int data;
	node* next;
};
node* create_list(int *a){
	node* ptr=new node;
	node* head=ptr; 
	ptr->next=NULL;
	for(int i=0;a[i]!=0;i++){
		node* new_node=new node;
		new_node->data=a[i];
		new_node->next=NULL;
		ptr->next=new_node;
		ptr=ptr->next;
	}

	return head;
}
node* Merge(int* a,int *b){
	node* head1=create_list(a);
	node* head2=create_list(b);
	node* ptr1=head1;
	node* ptr2=head2->next;
	while(ptr2!=NULL&&ptr1->next!=NULL){
		if(ptr2->data<ptr1->next->data){
			node* ptr=ptr2;
			ptr2=ptr2->next;
			ptr->next=ptr1->next;
			ptr1->next=ptr;
		}
		else{
			ptr1=ptr1->next;
		}
	}
	if(ptr1->next==NULL){
		ptr1->next=ptr2;
	}
	node *p=head1->next;
	return head1;
}
int main(){
	int a[100]={1,3,6,8,10,15};
	int b[100]={2,5,7,11,13,18};
	node* head=Merge(a,b);
	cout<<"表1为：1,3,6,8,10,15"<<endl<<"表2为：2,5,7,11,13,18"<<endl<<"合并两表后：";
	node* ptr=head->next;
	while(ptr!=NULL){
		cout<<ptr->data<<" ";
		ptr=ptr->next; 
	}
} 
