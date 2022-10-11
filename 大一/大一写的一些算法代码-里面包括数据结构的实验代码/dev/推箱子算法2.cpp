#include<iostream>
using namespace std;
#include<queue>
#include<math.h>
int m,n,b=1,j=0;

int state[100000][10][9][11]={0};//最多9个箱子，1个人和b-1个箱子 ,0代表x,1代表y 
int map[9][11]={
	{1,1,1,1,1,0,0,0,0,0,0},
	{1,5,0,0,1,0,0,0,0,0,0},
	{1,0,4,4,1,0,1,1,1,0,0},
	{1,0,0,0,1,0,1,3,1,0,0},
	{1,1,0,0,1,1,1,3,1,0,0},	//第2关地图 
	{0,1,0,0,0,0,0,0,1,0,0},
	{0,1,0,0,0,1,0,0,1,0,0},
	{0,1,0,0,1,1,1,1,1,0,0},
	{0,1,1,1,1,0,0,0,0,0,0},
};//1,3,2,2,2,3
int next[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct node{
	int *x,*y;
	node (int *x1,int *y1){
		x=x1;
		y=y1;
	}
};
bool judge1(int *x,int *y){
	int t;
	for(int c=0;c<j;c++){
		t=1;
		for(int i=0;i<b;i++){
			if(state[c][i][x[i]][y[i]]==0){
				t=0;
			}
			}
	
		if(t==1)
			return false;				
		}
		 
		return true;
}
bool judge2(int *x,int *y){
	for(int i=0;i<b;i++)
		for(int r=i+1;r<b;r++)
			if(x[i]==x[r]&&y[i]==y[r])
				return false;
	return true;
}
void mark(int *x,int *y){
	for(int i=0;i<b;i++)
	{
		state[j][i][x[i]][y[i]]=1;
	}
	j++;
	if(j>100000)
		cout<<"超出范围!"<<endl;
}
bool bound(int x,int y){
	if(x>=0&&x<m&&y>=0&&y<n&&map[x][y]!=1)
		return true;
	else
		return false;
}


int bfs(int *x,int *y){
	queue<node>q;
	node h(x,y);
	q.push(h);
	mark(x,y);
	while(!q.empty()){
		node head=q.front();
		q.pop();
	//	cout<<head.px<<","<<head.py<<endl;
	//	cout<<head.x[0]<<","<<head.x[1]<<endl;
		for(int w=0;w<4;w++)
	{
			
			int p,k=0;
			int *x1=new int[b],*y1=new int[b];
			x1[0]=head.x[0]+next[w][0];
			y1[0]=head.y[0]+next[w][1];
			for(int i=1;i<b;i++)
			{
				x1[i]=head.x[i];
				y1[i]=head.y[i];
			}
			for(int z=1;z<b;z++){
			if(x1[0]==x1[z]&&y1[0]==y1[z]){
						p=z;
						k=1;
						//cout<<"1231312321321";
					}
						
			}
			if(k){
			x1[p]=head.x[p]+next[w][0];
			y1[p]=head.y[p]+next[w][1];
				
				if(!bound(x1[0],y1[0])||!bound(x1[p],y1[p])||!judge2(x1,y1)||!judge1(x1,y1)){
								continue;
				}
				//cout<<"j="<<j<<","<<px<<","<<py<<","<<bx[0]<<","<<by[0]<<","<<bx[1]<<","<<by[1]<<endl;
//				cout<<"w="<<w<<endl;
//				cout<<"p="<<p<<"；"<<x1[0]<<","<<y1[0]<<"；"<<x1[1]<<","<<y1[1]<<"；"<<x1[2]<<","<<y1[2]<<endl;
				int s=1;
				for(int i=1;i<b;i++){
				if(map[x1[i]][y1[i]]!=3){
					s=0;
				}	
			}
				if(s){
				for(int i=0;i<b;i++){
					cout<<"x1["<<i<<"]="<<x1[i]<<","<<"y1["<<i<<"]="<<y1[i]<<";"<<endl;
				}
				return 1;
				}
				mark(x1,y1);
				q.push(node(x1,y1));
			}
			else{
			if(bound(x1[0],y1[0])&&judge1(x1,y1)){
			
			mark(x1,y1);
			q.push(node(x1,y1));
			}
		}	
	}
}			 
	return 0;	
}

int main(){
	//1,3,2,1,2,2,2,3//4代表箱子，1代表墙，3代表目标，5代表人 
	m=9;
	n=11;
	int x[3]={0};
	int y[3]={0};
	for(int i=0;i<m;i++)
		for(int k=0;k<n;k++){
			if(map[i][k]==5){
					x[0]=i;
					y[0]=k;
			}
			if(map[i][k]==4){
					x[b]=i;
					y[b]=k;
					b++;
			}
			cout<<b<<endl;
		}
	
	if(bfs(x,y)){
		cout<<"ok,finish1"<<endl; 
	}
	else
		cout<<"NO find! "<<endl;
}
