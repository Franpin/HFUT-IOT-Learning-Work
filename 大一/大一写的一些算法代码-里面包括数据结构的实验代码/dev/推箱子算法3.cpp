#include<iostream>
#include<queue>
#include<time.h>
#include<windows.h>
using namespace std;
int m,n,b=1,j=0,step=0;
struct people{
	int x;
	int y;
};
people people_path[10000];
struct re{
	int data;
	int x;
	int y;
	int a;
};
re state[100000][10][9][11];//最多9个箱子，1个人和b-1个箱子 ,0代表x,1代表y 
int map[9][11]={
	{0,1,1,1,1,1,1,1,1,1,1},
	{0,1,0,0,0,0,0,0,1,0,1},
	{0,1,0,0,0,0,4,0,1,0,1},
	{0,1,0,3,1,3,0,0,1,1,1},
	{0,1,0,1,1,1,0,0,1,1,0},	//第5关地图
	{1,1,0,0,1,0,0,0,1,1,0},
	{1,0,4,0,0,0,0,0,1,1,0},
	{1,5,0,0,0,0,0,0,1,1,0},
	{1,1,1,1,1,1,1,1,1,1,0},			
};//1,3,2,2,2,3
int next[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct node{
	int *x,*y,j0;
	node (int *x1,int *y1,int j1){
		x=x1;
		y=y1;
		j0=j1;
	}
};
bool judge1(int *x,int *y){
	int t;
	for(int c=0;c<j;c++){
		t=1;
		for(int i=0;i<b;i++){
			if(state[c][i][x[i]][y[i]].data==0){
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
		state[j][i][x[i]][y[i]].data=1;
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
	node h(x,y,j);
	q.push(h);
	mark(x,y);
	while(!q.empty()){
		node head=q.front();
		q.pop();
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
				state[j][0][x1[0]][y1[0]].x=head.x[0];
				state[j][0][x1[0]][y1[0]].y=head.y[0];
				state[j][0][x1[0]][y1[0]].a=head.j0;
				mark(x1,y1);
				q.push(node(x1,y1,j-1));
				int s=1;
				for(int i=1;i<b;i++){
				if(map[x1[i]][y1[i]]!=3){
					s=0;
				}	
			}
				if(s){
				j--;
				int x2=x1[0];
				int y2=y1[0];
				int j2=j; 
				people_path[0].x=x2;
				people_path[0].y=y2; 
				for(int i=1;j2!=0;i++){	
					
				int	x3=x2;
				int	y3=y2;
				int	j3=j2;
				step=i;
				x2=state[j3][0][x3][y3].x;
				y2=state[j3][0][x3][y3].y;
				j2=state[j3][0][x3][y3].a;
				people_path[i].x=x2;
				people_path[i].y=y2;
				}
				return 1;
				}			
			}
			else{
			if(bound(x1[0],y1[0])&&judge1(x1,y1)){
			state[j][0][x1[0]][y1[0]].x=head.x[0];
			state[j][0][x1[0]][y1[0]].y=head.y[0];
			state[j][0][x1[0]][y1[0]].a=head.j0;
			mark(x1,y1);
			q.push(node(x1,y1,j-1));
			}
		}	
	}
}			 
	return 0;	
}
void show_image(){
	for(int i=0;i<m;i++){
		for(int f=0;f<n;f++)
		{
			switch(map[i][f]){
				case 0:
					cout<<"  ";	
					break;
				case 1:
					cout<<"■";	
					break;
				case 3:
					cout<<"☆";	
					break;
				case 4:
					cout<<"□";	
					break;
				case 5:
					cout<<"♀";	
					break;
				case 6:
					cout<<"★";
					break; 
			}
			
			
		}
		cout<<endl;
} 		
}
void move_box(){
	for(int i=step;i>=0;i--)
	{
		int x=people_path[i].x;
		int y=people_path[i].y;
		if(map[x][y]==4||map[x][y]==6){	
			int move_x,move_y;
				move_x=x-people_path[i+1].x;
				move_y=y-people_path[i+1].y;	
				
				if(map[x+move_x][y+move_y]==3)
					map[x+move_x][y+move_y]=6;
				if(map[x+move_x][y+move_y]==0)
					map[x+move_x][y+move_y]=4;					
		}
		if(map[x][y]==3||map[x][y]==6){
		map[x][y]=5;
		show_image();
		Sleep(300);
		system("cls");
		map[x][y]=3;
	}
		else{
		map[x][y]=5;
		
		show_image();
		Sleep(300);
		system("cls");
		map[x][y]=0;
			
		}
		}	
}
int main(){
	//1,3,2,1,2,2,2,3//4代表箱子，1代表墙，3代表目标，5代表人 
	m=9;
	n=11;
	int x[10]={0};
	int y[10]={0};
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
		}
	
	if(bfs(x,y)){
		cout<<"正在搜索中..."<<endl; 
		move_box();
		cout<<"ok,finish1"<<endl; 
	}
	else
		cout<<"NO find! "<<endl;
}
