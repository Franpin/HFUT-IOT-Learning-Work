#include <iostream>
#include "stack1.cpp"
using namespace std;
void transform(){
	int data;
	cout<<"请输入一个十进制数：";
	cin>>data;
	stack<int>s;
	while(data%16!=0){
		if(s.fullstack()){
			cout<<"can't push because the stack is full"<<endl;
			break;
		}
		else{
			s.push(data%16);
			data=data/16;
		}
	}
	cout<<"它的十六进制数为：0x"; 
	while(!s.empty()){
		cout<<s.pop();	
	}
	cout<<endl;
}
void judgement(){
	char str[100];
	stack<char>s;
	cout<<"请输入一个表达式：";
	cin>>str; 
	for(int i=0;str[i]!=0;i++){
		switch(str[i]){
			case '{':
				if(s.gettop()=='('||s.gettop()=='['||s.gettop()=='{'){
					cout<<"该表达式不合法！"<<endl;
					return ;
				}
				s.push(str[i]);
				break;
			case '[':
				if(s.gettop()=='('||s.gettop()=='['){
					cout<<"该表达式不合法！"<<endl;
					return ;
				}
				s.push(str[i]);
				break; 
			case '(':
				if(s.gettop()=='('){
					cout<<"该表达式不合法！"<<endl;
					return ;
				}

				s.push(str[i]);
				break; 
			case '}':
				if(s.pop()!='{'){
					cout<<"该表达式不合法！"<<endl;
					return ;
				}
				break;
			case ']':
				if(s.pop()!='['){
					cout<<"该表达式不合法！"<<endl;
					return ;
				}
					break;	
			case ')':
				if(s.pop()!='('){
					cout<<"该表达式不合法！"<<endl;
					return ;
				}
				break;
		}
	}
	if(!s.empty()){
		cout<<"该表达式不合法！"<<endl;
			return ;
	}

	cout<<"该表达式合法"<<endl;
	
} 
int main(int argc, char** argv) {
	transform();
	judgement();
	
	return 0;
}
