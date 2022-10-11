#include<iostream>
using namespace std;
int maze[5][5]={
	{4,4,4,4,4},
	{4,0,0,0,4},
	{4,0,0,6,4},
	{4,0,0,0,4},
	{4,4,4,4,4},
};
int vis[5][5]={0};
int in(int x,int y){
	if(x>=0&&x<5&&y>=0&&y<5)
		return 1;
	else
		return 0;
}
int dfs(int x,int y){
	if(maze[x][y]==6){
		vis[x][y]=1;
		maze[x][y]=1;
		return 1;
	}
	vis[x][y]=1;
	maze[x][y]=1;
	int tx=x;
	int ty=y+1;	
	if(in(tx,ty)&&maze[tx][ty]!=4&&!vis[tx][ty]){
		if(dfs(tx,ty))
			return 1;
	}
	tx=x;
	ty=y-1;	
	if(in(tx,ty)&&maze[tx][ty]!=4&&!vis[tx][ty]){
		if(dfs(tx,ty))
			return 1;
	}
	tx=x+1;
	ty=y;	
	if(in(tx,ty)&&maze[tx][ty]!=4&&!vis[tx][ty]){
		if(dfs(tx,ty))
			return 1;
	}
	tx=x-1;
	ty=y;	
	if(in(tx,ty)&&maze[tx][ty]!=4&&!vis[tx][ty]){
		if(dfs(tx,ty))
			return 1;
	}
	maze[x][y]=0;
	vis[x][y]=0; 
	return 0;
}
int main(){
	dfs(2,0);
	for (int i = 0 ; i < 5;i++){
		for( int j = 0 ; j <5 ; j++)
			cout <<maze[i][j];
			cout<<endl;
	}
	return 0; 
}
 
