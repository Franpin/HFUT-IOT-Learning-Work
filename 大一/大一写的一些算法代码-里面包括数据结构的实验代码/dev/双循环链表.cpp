#include<iostream>
using namespace std;
struct node{
	int data;
	node* pre;
	node* next; 
};
class doubleList{
	public:
		int len_size;
		node *head; 
		doubleList(int n){
			head=new node;
			head->next=head;
			head->pre=head;
			len_size=n;
			create_List();	
		}
		void create_List(){
			node *ptr=head;
			for(int i=0;i<len_size;i++){
				node *new_node=new node;
				new_node->data=i;
				ptr->next=new_node;
				new_node->pre=ptr;
				ptr=ptr->next; 
		}
			ptr->next=head;
			head->pre=ptr;	
		}
		void insert_element(int pos,int x){
			node* ptr=head->next;
			for(int i=1;i<pos;i++){
				ptr=ptr->next;
			}
			node *new_node=new node;
			new_node->data=x;
			new_node->pre=ptr->pre;
			new_node->next=ptr;
			ptr->pre=new_node;
			new_node->pre->next=new_node;
			ptr=head->next;
			while(ptr!=head){
				cout<<ptr->data<<" ";
				ptr=ptr->next;	
			}	
			cout<<endl; 
		}
		void delete_element(int pos){
			node* ptr=head->next;
			for(int i=1;i<pos;i++){
				ptr=ptr->next;
			}
			ptr->pre->next=ptr->next;
			ptr->next->pre=ptr->pre;
			delete []ptr;
			ptr=head->next;
			while(ptr!=head){
				cout<<ptr->data<<" ";
				ptr=ptr->next;	
			}
			cout<<endl;	
		} 		
};
int main(){
	doubleList List(8);
	List.insert_element(1,66);
	List.delete_element(9);
	return 0;
}
