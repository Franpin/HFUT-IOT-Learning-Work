#include<iostream>
using namespace std;
int a[]={50,30,120,25,3,85,40,100,12,90,15,60, 35,9,110}; 
void swap(int &a,int &b){
	int t=a;
	a=b;
	b=t;
}
int f(){
	for(int i=0;i<14;i++){
	for(int i=0;i<14;i++){
		if(a[i]>a[i+1]){
			swap(a[i],a[i+1]);
		}
	}
	for(int i=0;i<15;i++){
		if(i==14){
				cout<<a[i];
			}
			else
			cout<<a[i]<<"¡¢"; 
	}
	cout<<endl;
}
}
int g(){
	for(int i=1;i<15;i++){
		for(int j=i;j>0;j--){
			if(a[j]<a[j-1]){
				swap(a[j],a[j-1]);
			}
		}
		for(int i=0;i<15;i++){
			if(i==14){
				cout<<a[i];
			}
			else
			cout<<a[i]<<"¡¢"; 
		}
		cout<<endl;
	}
}
void z(){
	for(int i=0;i<15;i++){
		int min=i;
		for(int j=i+1;j<15;j++){
			if(a[j]<a[min]){
				min=j;
			}
		}
		if(min!=i)
			swap(a[i],a[min]);
		for(int i=0;i<15;i++){
			if(i==14){
				cout<<a[i];
			}
			else
			cout<<a[i]<<"¡¢"; 
		}
		cout<<endl;
	}
	
}
int main(){
	z();
	
}
