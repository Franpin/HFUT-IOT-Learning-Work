#include<iostream>
using namespace std;
void f(char from,char to,char mid,int n){
	if(n==1)
		cout<<from<<"->"<<to<<endl;
	else{
	f(from,mid,to,n-1);
	cout<<from<<"->"<<to<<endl;
	f(mid,to,from,n-1);
}
}
int main(){
	f('A','C','B',5);	
}
