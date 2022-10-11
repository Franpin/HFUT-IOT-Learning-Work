#include<iostream>
using namespace std;
#include<queue>
bool in(int x,int y){
	if(x>=0&&x<5&&y>=0&&y<5)
		return true;
	else
		return false;
}
int step=0;
struct node{
	int data;
	int x;
	int y;
};
node pre;
int map[5][5]={
	{4,0,0,4,6},
	{4,0,4,0,0},
	{4,4,4,0,4},
	{4,0,0,0,4},
	{4,0,4,4,4}, 
};
int next[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
node vis[5][5];
int bfs(node head){
	queue<node>q;
	q.push(head);
	while(!q.empty()){
		int tx,ty;
		node ht;
		head=q.front();
		q.pop();
		for(int i=0;i<4;i++)
	{
			tx=head.x+next[i][0];
			ty=head.y+next[i][1];
			if(in(tx,ty)&&!vis[tx][ty].data&&map[tx][ty]!=4){
				step=head.data+1;
				if(map[tx][ty]==6)
				{
					vis[tx][ty]=head;
					cout<<step<<endl;
					pre=vis[tx][ty];
					return 1;
				}
				ht.x=tx;
				ht.y=ty;
				ht.data=step;
				vis[tx][ty]=head;
				q.push(ht);
		}
	}
}			 
	return 0;	
}
int main(){
	node head;
	head.x=3;
	head.y=1;
	head.data=0;
	vis[4][1].data=0; 
	if(bfs(head)){
		while(step){
			map[pre.x][pre.y]=1;
			pre=vis[pre.x][pre.y];	
			step--;	
			}
		for(int i=0;i<5;i++){ 
			for(int j=0;j<5;j++)
				cout<<map[i][j];
			cout<<endl;
	}
}
	else
		cout<<"NO find! "<<endl;
} 
