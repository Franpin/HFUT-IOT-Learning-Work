#include<iostream>
#include <string>
#include <math.h>
using namespace std;
class Parse{
	public:
		int a;
		int b;
		Parse(string s){
			a=0;
			b=0;
			int s1[50];
			for(int i=0;i<50;i++){
				s1[i]=-1;
			}
			for(int i=0;i<s.length();i++){
				if(s[i]>=48&&s[i]<=57){
						s1[i]=s[i]-'0';
				}		
			}

			int j;
			for(j=49;s1[j]==-1;j--){
			}
			int k;
			for(k=0;s1[j-k]!=-1;k++){
				a+=pow(10,k)*s1[j-k];
			}
			int x;
			for(x=j-k;s1[x]==-1;x--){
			}
			for(int p=0;s1[x-p]!=-1;p++){
				b+=pow(10,p)*s1[x-p];
			}
		}
		int getFirst(){
			return b;
		} 
		int getLast(){
			return a;
		}
};
int main(){
	string s="ab@r$&+fe321-54103@@@+==fsa.";
	Parse P(s);
	cout<<P.getFirst()<<endl<<P.getLast()<<endl;
	
}
