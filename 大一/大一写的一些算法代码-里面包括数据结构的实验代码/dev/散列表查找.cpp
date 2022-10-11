#include<iostream>
using namespace std;
int main(){
	int a[11];
	for(int i=0;i<11;i++){
		a[i]=11;
	}
	int data[7]={1,7,9,23,44,66,72};
	for(int i=0;i<7;i++){	
		int t=data[i]%11;
		if(a[t]==11){
			a[t]=data[i];
		}
		else{
			for(int j=t+1;j<t+11;j++){
				if(a[j%11]==11){
					a[j%11]=data[i];
					break; 
				}
			} 
		}
	} 
	int x;
	cout<<"请输入要查找的元素："<<endl;
	cin>>x;
	int t=x%11;
	for(int i=t;i<t+11;i++){
		if(a[i%11]==x){
			cout<<"查找成功！该元素下标为："<<i%11<<endl;	
			return i; 
		}
	}
	cout<<"查找失败！"<<endl;
	return -1;
}
