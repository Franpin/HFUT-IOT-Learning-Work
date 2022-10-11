#ifndef STACK1_H
#define STACK1_H
#include <iostream>
using namespace std; 
template<class T>
class stack
{
	public:
		stack();
		~stack();
		T gettop(){return a[p];}
		void push(T x);
		bool fullstack();
		bool empty();
		T pop();
		T *a;
		int p;
		int maxsize;
};
template<typename T>
stack<T>::stack()
{	
	maxsize=10000;
	a=new T[maxsize];
	p=-1;

}
template<typename T>
stack<T>::~stack()
{ 
	delete []a;
}
template<typename T>
bool stack<T>:: fullstack(){
	if(p==maxsize){
		return true;
	}
	return false;
}
template<typename T>
bool stack<T>::empty(){
	if(p==-1){
		return true;
	}
	return false;
}
template<typename T>
void stack<T>::push(T x){
	if(fullstack()){
		cout<<"the stack is full!"<<endl;
		return ;
	}
	p++;
	a[p]=x;
}
template<typename T>
T stack<T>::pop(){
	if(empty()){
		cout<<"the stack is empty!"<<endl;
		return 0;
	}
	p--;
	return a[p+1];
}


#endif
