#include<iostream>
using namespace std;
void swap(int &a,int &b){
	int t=a;
	a=b;
	b=t;
}
void sort1(int *a){
	for(int m=0;m<0;m++)
	for(int i=0;i<9;i++){
		if(a[i]<a[i+1])
			swap(a[i],a[i+1]); 
	}
}
void sort2(int a[]){
	for(int i=0;i<9;i++){
		if(a[i]<a[i+1])
			swap(a[i],a[i+1]); 
	}
}
int main(){
	int a[10]={1,3,4,12,34,45,56,57,23,34};
	sort1(a);
	for(int i=0;i<10;i++)
		cout<<a[i]<<" ";
}

