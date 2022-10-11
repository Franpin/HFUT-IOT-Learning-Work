#include<iostream>
using namespace std;
int vis[100][100];
int path[100][100];
int sum=0;
int N; 
void print_Method(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(vis[i][j]==1){
				cout<<"("<<i<<","<<j<<")"<<" "; 
			}
		}
	}
	
} 
int judge(int r,int c){

    for(int i=0;i<N;i++){
    	if(vis[i][c])
     		return 0;
    }
 	for(int i=r,j=c;i>=0&&j>=0;i--,j--){
     	if(vis[i][j])
     		return 0;
   }
   for(int i=r,j=c;i>=0&&j<N;i--,j++){
    	if(vis[i][j])
    	return 0;
   }
     return 1;
 }
int queen(int r){
	if(r==N){
		cout<<"这是第"<<sum+1<<"种方法"<<endl; 
		print_Method();	
		cout<<endl;
	    sum++;
	    return 1;
	}
	for(int i=0;i<N;i++){
	    if(judge(r,i)){
		     vis[r][i]=1;
		     path[r][i]=1;
			queen(r+1);
		    vis[r][i]=0;
	    }
	 } 	
	return 0;
	
}

int main(){
	cin>>N; 
	queen(0);
	cout<<"总共的路径："<<sum<<endl; 
	return 0;
}
