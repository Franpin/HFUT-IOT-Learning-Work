#include <iostream>
using namespace std;
int vis[8][8] = { 0 };
int step[8][2] = { {-2,-1} ,{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2} };
void dfs(int x,int y){
	for(int i=0;i<8;i++){
		int hx=x+step[i][0];
		int hy=y+step[i][1];
		if(vis[hx][hy]==0&&hx>=0&&hy>=0&&hx<8&&hy<8){
			vis[hx][hy]=1;
			dfs(hx,hy);
			cout<<"("<<hx<<","<<hy<<")"<<" ";
			
		}
	}
	
}
int main(){
	int x,y;
	cin>>x>>y; 
	dfs(x,y);

	return 0;
}
