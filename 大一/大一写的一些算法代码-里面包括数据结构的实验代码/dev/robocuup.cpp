#include<iostream>
#include<set> 
#include <algorithm>
using namespace std;
int find(){
	int a1[]={1,2,3,4,6};
	int a2[]={2,3,4,5,8,10};
	set<int>s1(a1,a1+5);
	set<int>s2(a2,a2+6);
	set<int>s3;
	set<int>::iterator it1;
	set<int>::iterator it2;
	for(it1=s1.begin();it1!=s1.end();it1++) 
    	for(it2=s2.begin();it2!=s2.end();it2++){
    		if(*it1==*it2){
    			s3.insert(*it1);
			}
		} 
	set<int>::iterator it;
	cout<<"俩集合的交集是：";
	for(it=s3.begin();it!=s3.end();it++){
		cout<<*it<<" ";
	}
  
}
int main(){
	find();
} 
