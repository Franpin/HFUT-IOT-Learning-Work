#include<iostream>
using namespace std;
struct node{
	char data;
	node* next;
};
int Graph[4][4]={
	{0,4,5,3},
	{0,0,2,0},
	{0,0,0,0},
	{0,0,6,0}
};
void transform(node* a,char* list){
	for(int i=0;i<4;i++){
		node* ptr=a+i;
		for(int j=0;j<4;j++){
			if(Graph[i][j]!=0){
				node* new_node=new node;
				new_node->data=list[j];
				new_node->next=NULL;
				ptr->next=new_node;
				ptr=ptr->next;
			}
		}
	}
}
void find_node(node* a,int *in_node,int *out_node,char* list){
	for(int i=0;i<4;i++){
		node* ptr=a[i].next; 
		while(ptr){
			out_node[i]++;
			for(int k=0;k<4;k++){
				if(a[k].data==ptr->data){
					in_node[k]++; 
				}
			}
			ptr=ptr->next;
		}
	}
}
int main(){
	int in_node[4]={0};
	int out_node[4]={0};
	
	node* a=new node[4];
	char list[]="abcd";
	for(int i=0;i<4;i++){
		a[i].data=list[i];
		a[i].next=NULL;
	}
	transform(a,list);
	find_node(a,in_node,out_node,list); 
	for(int i=0;i<4;i++){
		cout<<a[i].data<<"的入度为"<<in_node[i]<<" "<<endl; 
	}
	for(int i=0;i<4;i++){
		cout<<a[i].data<<"的出度为："<<out_node[i]<<" "<<endl; 
	}
} 

