#include<iostream>
#include<string>
using namespace std;
string str1;
string str2;
string str[10][10];
int main(){
	cin>>str1>>str2;
	int num[100][100]={0};
	for(int i=1;i<str1.length()+1;i++){
		for(int j=1;j<str2.length()+1;j++){
			if(str1[i-1]==str2[j-1]){
				str[i][j]=str[i-1][j-1]+str1[i-1];
				num[i][j]=num[i-1][j-1]+1;

			}else{
				if(num[i-1][j]>num[i][j-1]){
					str[i][j]=str[i-1][j];
					num[i][j]=num[i-1][j];
				}else{
					str[i][j]=str[i][j-1];
					num[i][j]=num[i][j-1];
				}
				
			}
		}
	}
	cout<<str[str1.length()][str2.length()]<<endl;
	cout<<"num="<<num[str1.length()][str2.length()]<<endl;
}
