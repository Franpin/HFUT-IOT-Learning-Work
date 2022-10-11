#include<iostream>
using namespace std;
int next[2][2]={{1,0},{0,1}};
int stop[8][2]={{1,2},{2,1},{-1,2},{-2,1},{-1,-2},{-2,-1},{1,-2},{2,-1}};
int map[20][20]={0};
int step=0;
int m,n;
int hx,hy;
int horse(int x,int y){
	for(int i=0;i<8;i++){
		int tx=hx+stop[i][0];
		int ty=hy+stop[i][1];
		if(x==tx&&y==ty||x==hx&&y==hy){
			return 0;
		}
	}	
	return 1;
}
void bfs(int x,int y){
	for(int i=0;i<2;i++){
		int tx=x+next[i][0];
		int ty=y+next[i][1];
		if(tx>=0&&tx<=n&&ty>=0&&ty<=m&&horse(tx,ty)){
			if(tx==n&&ty==m){
				step++;
				return ;
			}			
			bfs(tx,ty);	
		}
	}	
}
int main(){
	scanf("%d %d %d %d",&n,&m,&hx,&hy);
	
	bfs(0,0);
	cout<<step<<endl;
return 0;	
}
