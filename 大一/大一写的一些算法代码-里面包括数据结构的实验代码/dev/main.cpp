#include <iostream>
#include "stack1.cpp"
using namespace std;
void transform(){
	int data;
	cout<<"������һ��ʮ��������";
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
	cout<<"����ʮ��������Ϊ��0x"; 
	while(!s.empty()){
		cout<<s.pop();	
	}
	cout<<endl;
}
void judgement(){
	char str[100];
	stack<char>s;
	cout<<"������һ�����ʽ��";
	cin>>str; 
	for(int i=0;str[i]!=0;i++){
		switch(str[i]){
			case '{':
				if(s.gettop()=='('||s.gettop()=='['||s.gettop()=='{'){
					cout<<"�ñ��ʽ���Ϸ���"<<endl;
					return ;
				}
				s.push(str[i]);
				break;
			case '[':
				if(s.gettop()=='('||s.gettop()=='['){
					cout<<"�ñ��ʽ���Ϸ���"<<endl;
					return ;
				}
				s.push(str[i]);
				break; 
			case '(':
				if(s.gettop()=='('){
					cout<<"�ñ��ʽ���Ϸ���"<<endl;
					return ;
				}

				s.push(str[i]);
				break; 
			case '}':
				if(s.pop()!='{'){
					cout<<"�ñ��ʽ���Ϸ���"<<endl;
					return ;
				}
				break;
			case ']':
				if(s.pop()!='['){
					cout<<"�ñ��ʽ���Ϸ���"<<endl;
					return ;
				}
					break;	
			case ')':
				if(s.pop()!='('){
					cout<<"�ñ��ʽ���Ϸ���"<<endl;
					return ;
				}
				break;
		}
	}
	if(!s.empty()){
		cout<<"�ñ��ʽ���Ϸ���"<<endl;
			return ;
	}

	cout<<"�ñ��ʽ�Ϸ�"<<endl;
	
} 
int main(int argc, char** argv) {
	transform();
	judgement();
	
	return 0;
}
