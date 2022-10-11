#ifndef STACK_H
#define STACK_H
#include<iostream>
using namespace std;
template<typename T>
struct node{
	T data;
	node<T> *next;
}; 
template<class T>
class stack
{
	public:
		stack();
		~stack();
		T gettop(){return p->data;}
		void push(T x);
		bool empty();
		T pop();
		node<T>* p;
};
template<typename T>
stack<T>::stack()
{
	p=NULL;
}
template<typename T>
stack<T>::~stack()
{ 
	delete []p;
}
template<typename T>
bool stack<T>::empty(){
	if(p==NULL){
		return true;
	}
	return false;
}
template<typename T>
void stack<T>::push(T x){
	node<T> *new_node =new node<T>;
	new_node->data=x;
	new_node->next=p;
	p=new_node; 
}
template<typename T>
T stack<T>::pop(){
	if(empty()){
		cout<<"the stack is empty!"<<endl;
		return 0;
	}
	node<T> *pre=p;
	p=p->next;
	return pre->data;
}

#endif
