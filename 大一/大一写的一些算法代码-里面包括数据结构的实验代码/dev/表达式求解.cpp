#include<stack>
#include<iostream>
using namespace std;
int transform(char c){
	switch(c){
		case '+':
			return 0;
			break;
		case '-':
			return 0;
			break;
		case '*':
			return 1;
			break;
		case '/':
			return 1;
			break;
//		case '(':
//			return -1;
//			break;
//		case ')';
//			return 2;
//			break;
	} 	
}
int main(){
	char str[100];
	cin>>str;
	int a[100];
	char b[100];
	int m=0,n=0;
	stack<int>s1;
	stack<char>s2;
	for(int i=0;str[i]!=0;i++){
		if(str[i]>=48&&str[i]<=57){
			a[m]=int(str[i]);
			m++
		}	
		else{
			b[n]=str[i];
		}
	}
	for(int i=0;a[i]!=0||b[i]!=0;i++){
		if(s1.empty()||s2.empty()){
			s1.push(a[i]);
			s2.push(b[i]);
		}
		else{
			s1.push(a[i]);
			char c=s2.top();
			if(transform(b[i])>transform(c){
				s2.push(b[i]);
			}
			else{
				s2.pop();
				switch(c){
					case '+':
						int a1=s1.top();
						s1.pop();
						int a2=s1.top();	
						s1.pop();
						s1.push(a1+a2);
						break;
					case '-':
						int a1=s1.top();
						s1.pop();
						int a2=s1.top();	
						s1.pop();
						s1.push(a1-a2);
						break;
					case '*':
						int a1=s1.top();
						s1.pop();
						int a2=s1.top();	
						s1.pop();
						s1.push(a1*a2);//注意还有空的情况 
						break;		
					case '/':
						int a1=s1.top();
						s1.pop();
						int a2=s1.top();	
						s1.pop();
						s1.push(a1/a2);
						break;		
										

					
				}
				
					
				
				
				
				
			}
			
			
			
		}
	}
	
} 

