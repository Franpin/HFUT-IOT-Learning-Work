#include<iostream>
#include<string.h>
typedef char* String;
using namespace std;
int next[255];

int get_next(String T){
	int i=1;
	int j=0;
	next[1]=0;
	while(i<T[0]){
		if(j==0||T[i]==T[j])
		{
			i++;
			j++;
			if(T[i]!=T[j])
			{
			next[i]=j;	
			}
			else
			{
				next[i]=next[j];//与前面相等时，如果这个位置失配，
								//那么next数组对应的T的元素也失配 
			}
		}
		else
		{
			
			j=next[j];
		}
		
	}
	return 0;
}
int Kmp(String S,String T){
	get_next(T);
	int i=1;
	int j=1;
	while(i<=S[0]&&j<=T[0])
	{
		if(j==0||T[j]==S[i])
		{
			j++;
			i++;
		}
		else
		{
			j=next[j];
		}
		
	}
	if(j>T[0]){
		cout<<"find"<<endl;
		return i-T[0];
	}	
	else
	{
		return 0;
	}
}
int main(){
	char T[255]=" aabab";
	char S[255]=" aabacca";
	T[0]=5;
	S[0]=7;
	get_next(T);
	Kmp(S,T);
	return 0;
}
