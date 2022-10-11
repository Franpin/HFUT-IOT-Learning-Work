#include <iostream>
#include <set>
using namespace std;
int find(){
	int a[5]={1,2,4,3,7};
	int b[5]={3,4,7,1,2}
	set<int> s1(a,a+5);
	set<int> s2(b,b+5);
	set<int> s3;
	for(int i=0;i<s1.size();i++){
		for(j=0;j<s2.size();j++){
			cout<<s1[i]<<end;
			if(s1[i]==s2[j]){
				s3.insert(s1[i]);
			}
		}
	}
	for(int i=0;i<s3.size();i++){
		cout<<s3[i]<<" ";
	}
}
int main(){
	find();
	
}
