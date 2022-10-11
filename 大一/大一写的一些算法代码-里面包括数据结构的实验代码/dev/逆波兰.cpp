#include<iostream>
#include"ctype.h"
#include<stdlib.h>
using namespace std;
class stack{
	public:
		int maxsize;
		int top;
		double *a;
		stack(){
			maxsize=100;
			a=new double[100];
			top=0;
		}
		~stack(){
			delete []a;
		} 
		void push(double x){
			a[top]=x;
			top++;
		}
		void pop(double &x){
			top--;
			x=a[top];
		}
		int lenth(){
			return top;
		}
}; 
int main(){
	int i=0;
	char str[100];
	stack stack1;
	cout<<"请输入逆波兰后缀表达式(以‘#’结尾)："<<endl;
	char c;	
	c=getchar();
	while(c!='#'){
		while(isdigit(c)||c=='.'){	
			str[i]=c;
			i++;
			c=getchar();
			if(c==' '){
				double d;
				d=atof(str);
				stack1.push(d);
				i=0;
				break;
			}
		}
		c=getchar();
		switch(c){
			double d1,d2;
			case '+':
				stack1.pop(d1);
				stack1.pop(d2);
				stack1.push(d1+d2);
				break;
			case '-':
				stack1.pop(d1);
				stack1.pop(d2);
				stack1.push(d1-d2);
				break;
			case '*':
				stack1.pop(d1);
				stack1.pop(d2);
				stack1.push(d1*d2);
				break;
			case '/':
				stack1.pop(d1);
				stack1.pop(d2);
				stack1.push(d2/d1);
				break;
		}	
	}
	double d;
		stack1.pop(d);
		cout<<"最终计算结果为："<<d<<endl;
		
	return 0;
} 
